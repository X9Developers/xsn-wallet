#ifndef WALLETASSETSLISTMODEL_HPP
#define WALLETASSETSLISTMODEL_HPP

#include <QObject>
#include <QHash>
#include <QAbstractListModel>
#include <memory>

class WalletAssetsModel;

class WalletAssetsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        IDRole,
        NameRole,
        TicketRole,
        ColorRole
    };
    explicit WalletAssetsListModel(QObject *parent = nullptr);
    virtual ~WalletAssetsListModel() override;

    virtual int rowCount(const QModelIndex &parent) const override final;
    virtual QVariant data(const QModelIndex &index, int role) const override final;
    virtual QHash<int, QByteArray> roleNames() const override final;

signals:

public slots:
    void initialize(QObject *appViewModel);

private:
    void initAssets(const WalletAssetsModel &assetModel);

private:
    struct WalletAssetsListModelImpl;
    std::unique_ptr<WalletAssetsListModelImpl> _impl;
};

#endif // WALLETASSETSLISTMODEL_HPP
