#ifndef WALLETDATASOURCE_HPP
#define WALLETDATASOURCE_HPP

#include <QObject>
#include <functional>
#include <Utils/Utils.hpp>
#include <Data/TransactionEntry.hpp>

class WalletDataSource : public QObject
{
    Q_OBJECT
public:
    using TransactionsList = std::vector<TransactionEntry>;
    explicit WalletDataSource(QObject *parent = nullptr);
    ~WalletDataSource();

    void fetchTransactions(int id);

signals:
    void transactionsFetched(int id, TransactionsList list);
    void transactionAdded(int id, TransactionEntry transaction);
    void transactionsFetchError(int id, QString error);

protected:
    virtual TransactionsList executeFetch(int id) = 0;

private:
    void initWorkerThread();

private:
    WorkerThread _dataSourceWorker;

};

#endif // WALLETDATASOURCE_HPP
