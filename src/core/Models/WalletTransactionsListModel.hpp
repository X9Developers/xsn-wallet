#ifndef WALLETTRANSACTIONSLISTMODEL_HPP
#define WALLETTRANSACTIONSLISTMODEL_HPP

#include <QAbstractListModel>
#include <QObject>
#include <QPointer>

#include "Models/WalletDataSource.hpp"
#include "Data/TransactionEntry.hpp"

class WalletTransactionsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WalletTransactionsListModel(QPointer<WalletDataSource> dataSource, AssetID assetID, QObject *parent = nullptr);
    ~WalletTransactionsListModel() override;

    enum Roles {
        TransactionIDRole,
        IsSendRole,
        DeltaRole,
        ImageUrlRole,
        TxDateRole
    };
    Q_ENUMS(Roles)

    virtual int rowCount(const QModelIndex &parent) const override final;
    virtual QVariant data(const QModelIndex &index, int role) const override final;
    virtual QHash<int, QByteArray> roleNames() const override final;

signals:

private slots:
    void onTransactionFetched(AssetID assetID, WalletDataSource::TransactionsList list);
    void onTransactionAdded(AssetID assetID, TransactionEntry entry);

private:
    void init();

private:
    QPointer<WalletDataSource> _walletDataSource;
    WalletDataSource::TransactionsList _transactionList;
    AssetID _assetID;
};

#endif // WALLETTRANSACTIONSLISTMODEL_HPP
