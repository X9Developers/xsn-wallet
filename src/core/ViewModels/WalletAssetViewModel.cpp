#include "WalletAssetViewModel.hpp"
#include "Models/WalletTransactionsListModel.hpp"
#include "Models/WalletDataSource.hpp"
#include "ViewModels/ApplicationViewModel.hpp"
#include "Data/WalletAssetsModel.hpp"
#include <Storage/KeyStorage.hpp>
#include <key_io.h>

//==============================================================================

WalletAssetViewModel::WalletAssetViewModel(QObject *parent) : QObject(parent)
{

}

//==============================================================================

WalletAssetViewModel::~WalletAssetViewModel()
{

}

//==============================================================================

QObject *WalletAssetViewModel::transactionsListModel()
{
    if(!_walletDataSource)
        return nullptr;

    if(_walletTransactionsListModels.count(_currentAssetID) == 0)
    {
        _walletTransactionsListModels.emplace(_currentAssetID, TransactionsListModelPtr(new WalletTransactionsListModel(_walletDataSource, _currentAssetID)));
    }
    return _walletTransactionsListModels.at(_currentAssetID).get();
}

//==============================================================================

QString WalletAssetViewModel::balance() const
{
    return QString("150 + 150 = 300");
}

//==============================================================================

WalletAssetViewModel::AssetID WalletAssetViewModel::currentAssetID() const
{
    return _currentAssetID;
}

//==============================================================================

void WalletAssetViewModel::initialize(ApplicationViewModel *applicationViewModel)
{
    _walletDataSource = applicationViewModel->dataSource();
    _walletAssetsModel = &applicationViewModel->assetsModel();
    currentAssetIDChanged();
}

//==============================================================================

QString WalletAssetViewModel::getReceivingAddress() const
{
    static KeyStorage keyStorage;
    auto derivedNewChildKey = keyStorage.deriveNewChildKey(0, 0, false);

    auto pubKey = derivedNewChildKey.second.key.GetPubKey();
    auto keyID = pubKey.GetID();

    return QString::fromStdString(bitcoin::EncodeDestination(keyID, _walletAssetsModel->assetById(_currentAssetID).params));
}

//==============================================================================

void WalletAssetViewModel::setCurrentAssetID(AssetID assetID)
{
    if(_currentAssetID != assetID)
    {
        _currentAssetID = assetID;
        currentAssetIDChanged();
    }
}

//==============================================================================

void WalletAssetViewModel::init()
{
}

//==============================================================================

