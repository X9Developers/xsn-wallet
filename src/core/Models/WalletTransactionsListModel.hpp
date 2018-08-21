#ifndef WALLETTRANSACTIONSLISTMODEL_HPP
#define WALLETTRANSACTIONSLISTMODEL_HPP


#include <QAbstractListModel>

class WalletTransactionsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WalletTransactionsListModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override final;
    virtual QVariant data(const QModelIndex &index, int role) const override final;
signals:

public slots:

};

#endif // WALLETTRANSACTIONSLISTMODEL_HPP
