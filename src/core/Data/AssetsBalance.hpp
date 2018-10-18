#ifndef ASSETBALANCE_HPP
#define ASSETBALANCE_HPP

#include "Utils/Common.hpp"
#include "Models/WalletDataSource.hpp"
#include "Data/TransactionEntry.hpp"
#include <map>
#include <QPointer>
#include <QObject>


class AllTransactionsDataSource;
class WalletAssetsModel;

class AssetsBalance : public QObject
{
    Q_OBJECT
public:
    using BalanceMap = std::map<AssetID, Balance>;
    explicit AssetsBalance(QPointer<WalletAssetsModel> walletAssetsModel, QPointer<AllTransactionsDataSource> dataSource, QObject *parent = nullptr);
    virtual ~AssetsBalance();

    BalanceMap balance() const;
    Balance balanceSum() const;
    Balance balanceById(AssetID assetID) const;

signals:
    void balanceUpdated();
    void assetBalanceUpdated(AssetID assetID);

private slots:
    void onTransactionFetched(WalletDataSource::TransactionsList list);
    void onTransactionAdded(TransactionEntry entry);

private:
    void init();
    void updateBalance();
    Balance calculateBalance(TransactionEntry transaction);

private:
    QPointer<WalletAssetsModel> _walletAssetsModel;
    WalletDataSource::TransactionsList _transactionList;
    QPointer<AllTransactionsDataSource> _dataSource;

    BalanceMap _assetsBalance;
};

#endif // ASSETBALANCE_HPP
