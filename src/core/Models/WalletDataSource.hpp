#ifndef WALLETDATASOURCE_HPP
#define WALLETDATASOURCE_HPP

#include <QObject>
#include <functional>
#include <Utils.hpp>
#include <Data/TransactionEntry.hpp>

class WalletDataSource : public QObject
{
    Q_OBJECT
public:
    using TransactionsList = std::vector<TransactionEntry>;
    explicit WalletDataSource(QObject *parent = nullptr);
    ~WalletDataSource();

    void fetchTransactions(QString id);

signals:
    void transactionsFetched(TransactionsList list);
    void transactionsFetchError(QString error);

protected:
    virtual TransactionsList executeFetch(QString id) = 0;

private:
    void initWorkerThread();

private:
    WorkerThread _dataSourceWorker;

};

#endif // WALLETDATASOURCE_HPP
