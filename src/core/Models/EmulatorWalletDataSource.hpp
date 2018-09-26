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

    void executeAdd(int assetID, int count);
    void clearTransactions(int assetID);

protected:
    TransactionsList executeFetch(int id) override;

private:
    void init();

private:
    std::map<int, TransactionsList> _transactionMap;
};

#endif // EMULATORWALLETDATASOURCE_HPP
