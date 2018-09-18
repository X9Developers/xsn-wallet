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
    ~EmulatorWalletDataSource() override;

    void executeAdd(QString modelName, int count);
    void clearTransactions(QString modelName);

protected:
    TransactionsList executeFetch(QString id) override;

private:
    void init();

private:
    std::map<QString, TransactionsList> _transactionMap;
};

#endif // EMULATORWALLETDATASOURCE_HPP
