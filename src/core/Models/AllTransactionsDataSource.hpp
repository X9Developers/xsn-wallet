#ifndef ALLTRANSACTIONSDATASOURCE_HPP
#define ALLTRANSACTIONSDATASOURCE_HPP

#include <QObject>
#include <Models/TransactionsDataSource.hpp>

class AllTransactionsDataSource : public TransactionsDataSource
{
    Q_OBJECT
public:
    explicit AllTransactionsDataSource(QPointer<WalletDataSource> dataSource, QObject *parent = nullptr);
    virtual void fetchTransactions() override final;

signals:

public slots:

};

#endif // ALLTRANSACTIONSDATASOURCE_HPP
