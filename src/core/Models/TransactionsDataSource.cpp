#include "TransactionsDataSource.hpp"

//==============================================================================

TransactionsDataSource::TransactionsDataSource(QPointer<WalletDataSource> dataSource, QObject *parent) :
    QObject(parent),
    _walletDataSource(dataSource)
{

}

//==============================================================================

TransactionsDataSource::~TransactionsDataSource()
{

}

//==============================================================================
