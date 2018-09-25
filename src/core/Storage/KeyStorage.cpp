#include "KeyStorage.hpp"
#include <key.h>
#include <utilstrencodings.h>
#include <chainparams.hpp>
#include <key_io.h>

#include <QDebug>

struct KeyStorage::KeyStorageImpl {
    std::map<ExtendedKeyPathBip44, bitcoin::CExtKey> _extKeys;
    bitcoin::CExtKey masterKey() const
    {
        bitcoin::CExtKey masterKey;             //hd master key
        auto seed = bitcoin::ParseHex("4b381541583be4423346c643850da4b320e46a87ae3d2a4e6da11eba819cd4acba45d239319ac14f863b8d5ab5a0d0c64d2e8a1e7d1457df2e5a3c51c73235be");
        masterKey.SetSeed(&seed[0], seed.size());
        return masterKey;
    }
};

KeyStorage::KeyStorage(QObject *parent) :
    QObject(parent),
    _impl(new KeyStorageImpl)
{
    bitcoin::ECC_Start();
}

KeyStorage::~KeyStorage()
{

}

static bitcoin::CExtKey DeriveExtKey(const bitcoin::CExtKey &parentKey, unsigned int nChild) {
    bitcoin::CExtKey result;
    parentKey.Derive(result, nChild);
    return result;
}

std::pair<ExtendedKeyPathBip44, bitcoin::CExtKey> KeyStorage::deriveNewChildKey(unsigned int coinType, unsigned int accountID, bool internal)
{
    using namespace bitcoin;


    // try to get the seed
    //    if (!GetKey(hdChain.seed_id, seed))
    //        throw std::runtime_error(std::string(__func__) + ": seed not found");

    ExtendedKeyPathBip44 path(coinType, accountID, internal);

    static unsigned int nInternalChainCounter = 0;
    static unsigned int nExternalChainCounter = 0;

    CExtKey childKey = deriveKeyForPath(path);

#if 0
    // derive child key at next index, skip keys already known to the wallet
    do {
        // always derive hardened keys
        // childIndex | BIP32_HARDENED_KEY_LIMIT = derive childIndex in hardened child-index-range
        // example: 1 | BIP32_HARDENED_KEY_LIMIT == 0x80000001 == 2147483649

        if (internal) {
            //            chainChildKey.Derive(childKey, hdChain.nInternalChainCounter | BIP32_HARDENED_KEY_LIMIT);
            childKey = DeriveExtKey(chainChildKey, nInternalChainCounter);
            //            metadata.hdKeypath = "m/0'/1'/" + std::to_string(hdChain.nInternalChainCounter) + "'";
            //            hdChain.nInternalChainCounter++;
//            nInternalChainCounter++;
        }
        else {
            //            chainChildKey.Derive(childKey, hdChain.nExternalChainCounter | BIP32_HARDENED_KEY_LIMIT);
            childKey = DeriveExtKey(chainChildKey, nExternalChainCounter);
            //            metadata.hdKeypath = "m/0'/0'/" + std::to_string(hdChain.nExternalChainCounter) + "'";
            //            hdChain.nExternalChainCounter++;
//            nExternalChainCounter++;
        }
    } while (false/*HaveKey(childKey.key.GetPubKey().GetID())*/);
#endif

    path.addChild(internal ? nInternalChainCounter++ : nExternalChainCounter++);

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

