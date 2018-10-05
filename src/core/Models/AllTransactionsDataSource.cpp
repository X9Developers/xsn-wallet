#include "AllTransactionsDataSource.hpp"
#include <Models/WalletDataSource.hpp>

//==============================================================================

AllTransactionsDataSource::AllTransactionsDataSource(QPointer<WalletDataSource> dataSource, QObject *parent) : TransactionsDataSource(dataSource, parent)
{
    connect(_walletDataSource, &WalletDataSource::allTransactionsFetched, this, &TransactionsDataSource::transactionsFetched);
}

//==============================================================================

void AllTransactionsDataSource::fetchTransactions()
{
    _walletDataSource->fetchAllTransactions();
}

//==============================================================================
