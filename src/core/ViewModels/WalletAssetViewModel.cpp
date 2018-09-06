#include "WalletAssetViewModel.hpp"
#include "Models/WalletTransactionsListModel.hpp"
#include "Models/WalletDataSource.hpp"
#include "ViewModels/ApplicationViewModel.hpp"

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
    if(_currentAssetID.isEmpty() || !_walletDataSource)
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
    currentAssetIDChanged();
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

