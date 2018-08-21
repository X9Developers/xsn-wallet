#ifndef WALLETDATASOURCE_HPP
#define WALLETDATASOURCE_HPP

#include <QObject>
#include <Data/TransactionEntry.hpp>

class WalletDataSource : public QObject
{
    Q_OBJECT
public:
    using TransactionsList = std::vector<TransactionEntry>;
    explicit WalletDataSource(QObject *parent = nullptr);

    void fetchTransactions(QString id);

signals:
    void transactionsFetched(TransactionsList list);
    void transactionsFetchError(QString error);

};

#endif // WALLETDATASOURCE_HPP
