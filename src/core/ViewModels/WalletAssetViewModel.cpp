#include "WalletAssetViewModel.hpp"

#include <Models/WalletTransactionsListModel.hpp>

//==============================================================================

WalletAssetViewModel::WalletAssetViewModel(QObject *parent) : QObject(parent)
{
    init();
}

//==============================================================================

WalletAssetViewModel::~WalletAssetViewModel()
{

}

//==============================================================================

QAbstractListModel *WalletAssetViewModel::transactionsListModel() const
{
    return _walletTransactionsListModel.get();
}

//==============================================================================

QString WalletAssetViewModel::balance() const
{
    return QString("150 + 150 = 300");
}

//==============================================================================

void WalletAssetViewModel::init()
{
    initTransactionsListModel();
}

//==============================================================================

void WalletAssetViewModel::initTransactionsListModel()
{

}

//==============================================================================
