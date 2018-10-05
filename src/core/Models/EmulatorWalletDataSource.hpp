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

    void executeAdd(AssetID assetID, int count);
    void clearTransactions(AssetID assetID);

protected:
    TransactionsList executeFetch(AssetID id) override;
    TransactionsList executeFetchAll() override;

private:
    void init();

private:
    std::map<AssetID, TransactionsList> _transactionMap;
};

#endif // EMULATORWALLETDATASOURCE_HPP
