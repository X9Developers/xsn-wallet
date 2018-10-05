#ifndef TRANSACTIONSDATASOURCE_HPP
#define TRANSACTIONSDATASOURCE_HPP

#include <QObject>
#include <QPointer>
#include <Data/TransactionEntry.hpp>
#include "WalletDataSource.hpp"

class TransactionsDataSource : public QObject
{
    Q_OBJECT
public:
    explicit TransactionsDataSource(QPointer<WalletDataSource> dataSource,
                                    QObject *parent = nullptr);
    virtual ~TransactionsDataSource();
    virtual void fetchTransactions() = 0;

signals:
    void transactionsFetched(WalletDataSource::TransactionsList list);
    void transactionAdded(TransactionEntry entry);

public slots:

protected:
    QPointer<WalletDataSource> _walletDataSource;
};

#endif // TRANSACTIONSDATASOURCE_HPP
