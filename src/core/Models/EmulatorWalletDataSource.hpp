#ifndef EMULATORWALLETDATASOURCE_HPP
#define EMULATORWALLETDATASOURCE_HPP

#include "Models/WalletDataSource.hpp"
#include "Data/TransactionEntry.hpp"
#include <QObject>
#include <QMap>

class EmulatorWalletDataSource : public WalletDataSource
{
    Q_OBJECT
public:
    explicit EmulatorWalletDataSource(QObject *parent = nullptr);
    ~EmulatorWalletDataSource();

    TransactionsList executeFetch(QString id) override;

private:
    void init();

private:
    std::map<QString, TransactionsList> _transactionMap;
};

#endif // EMULATORWALLETDATASOURCE_HPP
