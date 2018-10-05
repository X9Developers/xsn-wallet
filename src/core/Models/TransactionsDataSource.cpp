#include "TransactionsDataSource.hpp"
#include <Models/WalletDataSource.hpp>

//==============================================================================

TransactionsDataSource::TransactionsDataSource(QPointer<WalletDataSource> dataSource, QObject *parent) :
    QObject(parent),
    _walletDataSource(dataSource)
{
    connect(_walletDataSource, &WalletDataSource::transactionAdded, this, &TransactionsDataSource::onTransactionAdded);
}

//==============================================================================

TransactionsDataSource::~TransactionsDataSource()
{

}

//==============================================================================

void TransactionsDataSource::onTransactionAdded(AssetID assetID, TransactionEntry entry)
{
    Q_UNUSED(assetID);
    transactionAdded(entry);
}

//==============================================================================
