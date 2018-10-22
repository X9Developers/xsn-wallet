#ifndef WALLETASSETSLISTMODEL_HPP
#define WALLETASSETSLISTMODEL_HPP

#include "Utils/Common.hpp"
#include <QObject>
#include <QHash>
#include <QAbstractListModel>
#include <memory>
#include <QPointer>

class WalletAssetsModel;
class AssetsBalance;

class WalletAssetsListModel :  public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        IDRole,
        NameRole,
        TicketRole,
        ColorRole,
        BalanceRole,
        PortfolioPercentageRole
    };
    explicit WalletAssetsListModel(QObject *parent = nullptr);
    virtual ~WalletAssetsListModel() override;

    virtual int rowCount(const QModelIndex &parent) const override final;
    virtual QVariant data(const QModelIndex &index, int role) const override final;
    virtual QHash<int, QByteArray> roleNames() const override final;

public slots:
    void initialize(QObject *appViewModel);
    void sortByColumn(QString columnName);
    void onAssetBalanceUpdated();

private:
    void initAssets(const WalletAssetsModel &assetModel);
    void initBalance(AssetsBalance *assetsBalance);
    Balance getAssetBalance(AssetID assetID) const;

private:
    struct WalletAssetsListModelImpl;
    std::unique_ptr<WalletAssetsListModelImpl> _impl;
    QPointer<AssetsBalance> _balance;
    Balance _balanceSum;
};

#endif // WALLETASSETSLISTMODEL_HPP
