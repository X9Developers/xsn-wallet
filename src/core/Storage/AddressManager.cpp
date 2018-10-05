#include "AddressManager.hpp"
#include "KeyStorage.hpp"
#include <key_io.h>

//==============================================================================

struct AddressManager::AddressManagerImpl {
    KeyStorage _keyStorage;
    std::unique_ptr<ExtendedKeyPathBip44> _pendingKey;
    std::unique_ptr<ExtendedKeyPathBip44> _pendingInternalKey;

    std::map<AssetID, Addresses> _addressesCache;
};

//==============================================================================

AddressManager::AddressManager(QObject *parent) :
    QObject(parent),
    _impl(new AddressManagerImpl)
{

}

//==============================================================================

AddressManager::~AddressManager()
{

}

//==============================================================================

QString AddressManager::externalAddress() const
{
//    if(!_impl->_pendingKey) {
//        _impl->_pendingKey.reset(new ExtendedKeyPathBip44(_impl->_keyStorage.deriveNewChildKey(0, 0, false)));
//    }

//    auto extKey = _impl->_keyStorage.extKeyForPath(*_impl->_pendingKey);
    return QString();
//    return bitcoin::EncodeExtKey(extKey, params);
}

//==============================================================================

QString AddressManager::changeAddress() const
{
    return QString();
}

//==============================================================================

AddressManager::Addresses AddressManager::addresses(AssetID assetID) const
{
    return _impl->_addressesCache.at(assetID);
}

//==============================================================================

void AddressManager::markAddressAsUsed(QString address)
{

}

//==============================================================================
