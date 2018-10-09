#ifndef WALLETTRANSACTIONSLISTMODEL_HPP
#define WALLETTRANSACTIONSLISTMODEL_HPP

#include <QAbstractListModel>
#include <QObject>
#include <QPointer>

#include "Models/WalletDataSource.hpp"

class TransactionsDataSource;
class WalletAssetsModel;

class WalletTransactionsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WalletTransactionsListModel(QPointer<TransactionsDataSource> dataSource, QPointer<const WalletAssetsModel> walletAssetsModel, QObject *parent = nullptr);
    ~WalletTransactionsListModel() override;

    enum Roles {
        TransactionIDRole,
        IsSendRole,
        DeltaRole,
        ImageUrlRole,
        TxDateRole,
        CurrencyRole,
        SymbolRole
    };
    Q_ENUMS(Roles)

    virtual int rowCount(const QModelIndex &parent) const override final;
    virtual QVariant data(const QModelIndex &index, int role) const override final;
    virtual QHash<int, QByteArray> roleNames() const override final;

signals:

private slots:
    void onTransactionFetched(WalletDataSource::TransactionsList list);
    void onTransactionAdded(TransactionEntry entry);

private:
    void init();

private:
    QPointer<TransactionsDataSource> _dataSource;
    QPointer<const WalletAssetsModel> _walletAssetsModel;
    WalletDataSource::TransactionsList _transactionList;
};

#endif // WALLETTRANSACTIONSLISTMODEL_HPP
