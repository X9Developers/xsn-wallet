#ifndef ASSETTRANSACTIONSDATASOURCE_HPP
#define ASSETTRANSACTIONSDATASOURCE_HPP

#include <QObject>
#include "TransactionsDataSource.hpp"

class AssetTransactionsDataSource : public TransactionsDataSource
{
    Q_OBJECT
public:
    explicit AssetTransactionsDataSource(AssetID assetID, QPointer<WalletDataSource> dataSource, QObject *parent = nullptr);
    virtual void fetchTransactions() override final;

signals:

private slots:
    void onTransactionFetched(AssetID assetID, WalletDataSource::TransactionsList list);

private:
    AssetID _assetID;
};

#endif // ASSETTRANSACTIONSDATASOURCE_HPP
