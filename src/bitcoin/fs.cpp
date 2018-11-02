#include <fs.h>

#ifndef WIN32
#include <fcntl.h>
#else
#include <codecvt>
#include <windows.h>
#endif

#include <memory>
#include <mutex>
#include <map>
#include <utilmemory.h>
#include <sync.h>

/** A map that contains all the currently held directory locks. After
 * successful locking, these will be held here until the global destructor
 * cleans them up and thus automatically unlocks them, or ReleaseDirectoryLocks
 * is called.
 */
static std::map<std::string, std::unique_ptr<fsbridge::FileLock>> dir_locks;
/** Mutex to protect dir_locks. */
static std::mutex cs_dir_locks;

namespace fsbridge {

FILE *fopen(const fs::path& p, const char *mode)
{
#ifndef WIN32
    return ::fopen(p.string().c_str(), mode);
#else
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>,wchar_t> utf8_cvt;
    return ::_wfopen(p.wstring().c_str(), utf8_cvt.from_bytes(mode).c_str());
#endif
}

#ifndef WIN32

static std::string GetErrorReason() {
    return std::strerror(errno);
}

FileLock::FileLock(const fs::path& file)
{
    fd = open(file.string().c_str(), O_RDWR);
    if (fd == -1) {
        reason = GetErrorReason();
    }
}

FileLock::~FileLock()
{
    if (fd != -1) {
        close(fd);
    }
}

bool FileLock::TryLock()
{
    if (fd == -1) {
        return false;
    }
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        reason = GetErrorReason();
        return false;
    }
    return true;
}
#else

static std::string GetErrorReason() {
    wchar_t* err;
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<WCHAR*>(&err), 0, nullptr);
    std::wstring err_str(err);
    LocalFree(err);
    return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(err_str);
}

FileLock::FileLock(const fs::path& file)
{
    hFile = CreateFileW(file.wstring().c_str(),  GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        reason = GetErrorReason();
    }
}

FileLock::~FileLock()
{
    if (hFile != INVALID_HANDLE_VALUE) {
        CloseHandle(hFile);
    }
}

bool FileLock::TryLock()
{
    if (hFile == INVALID_HANDLE_VALUE) {
        return false;
    }
    _OVERLAPPED overlapped = {0};
    if (!LockFileEx(hFile, LOCKFILE_EXCLUSIVE_LOCK | LOCKFILE_FAIL_IMMEDIATELY, 0, 0, 0, &overlapped)) {
        reason = GetErrorReason();
        return false;
    }
    return true;
}
#endif

std::string get_filesystem_error_message(const fs::filesystem_error& e)
{
#ifndef WIN32
    return e.what();
#else
    // Convert from Multi Byte to utf-16
    std::string mb_string(e.what());
    int size = MultiByteToWideChar(CP_ACP, 0, mb_string.c_str(), mb_string.size(), nullptr, 0);

    std::wstring utf16_string(size, L'\0');
    MultiByteToWideChar(CP_ACP, 0, mb_string.c_str(), mb_string.size(), &*utf16_string.begin(), size);
    // Convert from utf-16 to utf-8
    return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t>().to_bytes(utf16_string);
#endif
}

} // fsbridge

/**
 * Ignores exceptions thrown by Boost's create_directories if the requested directory exists.
 * Specifically handles case where path p exists, but it wasn't possible for the user to
 * write to the parent directory.
 */
bool TryCreateDirectories(const boost::filesystem::path &p)
{
    try
    {
        return fs::create_directories(p);
    } catch (const fs::filesystem_error&) {
        if (!fs::exists(p) || !fs::is_directory(p))
            throw;
    }

    // create_directories didn't create the directory, it had to have existed already
    return false;
}

bool LockDirectory(const boost::filesystem::path &directory, const std::string lockfile_name, bool probe_only)
{
    std::lock_guard<std::mutex> ulock(cs_dir_locks);
    fs::path pathLockFile = directory / lockfile_name;

    // If a lock for this directory already exists in the map, don't try to re-lock it
    if (dir_locks.count(pathLockFile.string())) {
        return true;
    }

    // Create empty lock file if it doesn't exist.
    FILE* file = fsbridge::fopen(pathLockFile, "a");
    if (file) fclose(file);
    auto lock = MakeUnique<fsbridge::FileLock>(pathLockFile);
    if (!lock->TryLock()) {
        return false;
//        return error("Error while attempting to lock directory %s: %s", directory.string(), lock->GetReason());
    }
    if (!probe_only) {
        // Lock successful and we're not just probing, put it into the map
        dir_locks.emplace(pathLockFile.string(), std::move(lock));
    }
    return true;
}

boost::filesystem::path GetDefaultDataDir()
{
    namespace fs = boost::filesystem;
    // Windows < Vista: C:\Documents and Settings\Username\Application Data\DashCore
    // Windows >= Vista: C:\Users\Username\AppData\Roaming\DashCore
    // Mac: ~/Library/Application Support/DashCore
    // Unix: ~/.dashcore
#ifdef WIN32
    // Windows
    return GetSpecialFolderPath(CSIDL_APPDATA) / "XSNWallet";
#else
    fs::path pathRet;
    char* pszHome = getenv("HOME");
    if (pszHome == NULL || strlen(pszHome) == 0)
        pathRet = fs::path("/");
    else
        pathRet = fs::path(pszHome);
#ifdef MAC_OSX
    // Mac
    return pathRet / "Library/Application Support/XSNWallet";
#else
    // Unix
    return pathRet / ".xsnwallet";
#endif
#endif
}

const boost::filesystem::path &GetDataDir()
{
    namespace fs = boost::filesystem;

    static boost::filesystem::path pathCached;
    static CCriticalSection csPathCached;

    LOCK(csPathCached);

    fs::path &path = pathCached;

    // This can be called during exceptions by LogPrintf(), so we cache the
    // value so we don't have to do memory allocations after that.
    if (!path.empty())
        return path;

    path = GetDefaultDataDir();

    fs::create_directories(path);

    return path;
}
