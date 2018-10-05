#include "AssetTransactionsDataSource.hpp"
#include "WalletDataSource.hpp"

//==============================================================================

AssetTransactionsDataSource::AssetTransactionsDataSource(AssetID assetID, QPointer<WalletDataSource> dataSource, QObject *parent) :
    TransactionsDataSource(dataSource, parent),
    _assetID(assetID)
{
    connect(_walletDataSource, &WalletDataSource::transactionsFetched, this, &AssetTransactionsDataSource::onTransactionFetched);
}

//==============================================================================

void AssetTransactionsDataSource::fetchTransactions()
{
    _walletDataSource->fetchTransactions(_assetID);
}

//==============================================================================

void AssetTransactionsDataSource::onTransactionFetched(AssetID assetID, WalletDataSource::TransactionsList list)
{
    if(_assetID != assetID)
    {
        return;
    }

    transactionsFetched(list);
}

//==============================================================================
