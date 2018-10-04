#ifndef WALLETDATASOURCE_HPP
#define WALLETDATASOURCE_HPP

#include <QObject>
#include <functional>
#include <Utils/Common.hpp>
#include <Utils/Utils.hpp>
#include <Data/TransactionEntry.hpp>

class WalletDataSource : public QObject
{
    Q_OBJECT
public:
    using TransactionsList = std::vector<TransactionEntry>;
    explicit WalletDataSource(QObject *parent = nullptr);
    ~WalletDataSource();

    void fetchTransactions(AssetID id);

signals:
    void transactionsFetched(AssetID id, TransactionsList list);
    void transactionAdded(AssetID id, TransactionEntry transaction);
    void transactionsFetchError(AssetID id, QString error);

protected:
    virtual TransactionsList executeFetch(AssetID id) = 0;

private:
    void initWorkerThread();

private:
    WorkerThread _dataSourceWorker;

};

#endif // WALLETDATASOURCE_HPP
