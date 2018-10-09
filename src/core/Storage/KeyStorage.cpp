#include "KeyStorage.hpp"
#include <key.h>
#include <utilstrencodings.h>
#include <chainparams.hpp>
#include <key_io.h>
#include <walletdb.h>

#include <QDebug>

//==============================================================================

struct KeyStorage::KeyStorageImpl {
    bitcoin::CHDChain _hdChain;
    bitcoin::CExtKey masterKey() const;
};

//==============================================================================

KeyStorage::KeyStorage(QObject *parent) :
    QObject(parent),
    _impl(new KeyStorageImpl)
{
    bitcoin::ECC_Start();
}

//==============================================================================

KeyStorage::~KeyStorage()
{

}

//==============================================================================

void KeyStorage::setHDChain(const bitcoin::CHDChain &hdChain)
{
    _impl->_hdChain = hdChain;
}

//==============================================================================

const bitcoin::CHDChain &KeyStorage::hdChain() const
{
    return _impl->_hdChain;
}

//==============================================================================

static bitcoin::CExtKey DeriveExtKey(const bitcoin::CExtKey &parentKey, unsigned int nChild)
{
    bitcoin::CExtKey result;
    parentKey.Derive(result, nChild);
    return result;
}

//==============================================================================

std::pair<ExtendedKeyPathBip44, bitcoin::CExtKey> KeyStorage::deriveNewChildKey(AssetID coinType, AccountIndex accountID, bool internal)
{
    using namespace bitcoin;

    ExtendedKeyPathBip44 path(coinType, accountID, internal);

    auto &accounts = _impl->_hdChain.accounts[coinType];
    auto &account = accounts[accountID];
    auto &internalChainCounter = account.nInternalChainCounter;
    auto &externalChainCounter = account.nExternalChainCounter;

    CExtKey childKey = deriveKeyForPath(path);

    path.addChild(internal ? internalChainCounter++ : externalChainCounter++);

//    secret = childKey.key;
//    metadata.hd_seed_id = hdChain.seed_id;
    // update the chain model in the database
//    if (!batch.WriteHDChain(hdChain))
//        throw std::runtime_error(std::string(__func__) + ": Writing HD chain model failed");

    return { path, childKey };
}

//==============================================================================

bitcoin::CExtKey KeyStorage::deriveKeyForPath(ExtendedKeyPathBip44 path)
{
    using namespace bitcoin;
    auto masterKey = _impl->masterKey();

    return std::accumulate(std::begin(path), std::end(path), masterKey, [](CExtKey accum, unsigned index) {
        return DeriveExtKey(accum, index);
    });
}

//==============================================================================

//bool KeyStorage::hasExtKeyForPath(const ExtendedKeyPathBip44 &path) const
//{
//    return _impl->_extKeys.count(path);
//}

////==============================================================================

//const bitcoin::CExtKey &KeyStorage::extKeyForPath(const ExtendedKeyPathBip44 &path) const
//{
//    return _impl->_extKeys.at(path);
//}

//==============================================================================

bitcoin::CExtKey KeyStorage::KeyStorageImpl::masterKey() const
{
    bitcoin::CExtKey masterKey;
    masterKey.SetSeed(&_hdChain.vchSeed[0], _hdChain.vchSeed.size());
    return masterKey;
}

//==============================================================================
