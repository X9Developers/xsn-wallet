#ifndef EMULATORWALLETDATASOURCE_HPP
#define EMULATORWALLETDATASOURCE_HPP

#include "Models/WalletDataSource.hpp"
#include "Data/TransactionEntry.hpp"
#include "Data/WalletAssetsModel.hpp"
#include <QObject>
#include <QMap>
#include <QPointer>

class EmulatorWalletDataSource : public WalletDataSource
{
    Q_OBJECT
public:
    explicit EmulatorWalletDataSource(QPointer<WalletAssetsModel> walletAssetsModel, QObject *parent = nullptr);
    ~EmulatorWalletDataSource() override;

    void executeAdd(AssetID assetID, int count);
    void clearTransactions(AssetID assetID);

protected:
    TransactionsList executeFetch(AssetID id) override;
    TransactionsList executeFetchAll() override;

private:
    void init();

private:
    QPointer<WalletAssetsModel> _walletAssetsModel;
    std::map<AssetID, TransactionsList> _transactionMap;
};

#endif // EMULATORWALLETDATASOURCE_HPP
