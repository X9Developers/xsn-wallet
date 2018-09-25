#include "AddressManager.hpp"
#include "KeyStorage.hpp"
#include <key_io.h>

//==============================================================================

struct AddressManager::AddressManagerImpl {
    KeyStorage _keyStorage;
    std::unique_ptr<ExtendedKeyPathBip44> _pendingKey;
    std::unique_ptr<ExtendedKeyPathBip44> _pendingInternalKey;
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

void AddressManager::markAddressAsUsed(QString address)
{

}

//==============================================================================
