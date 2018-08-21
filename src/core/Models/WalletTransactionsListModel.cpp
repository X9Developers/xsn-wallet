#include "WalletTransactionsListModel.hpp"

//==============================================================================

WalletTransactionsListModel::WalletTransactionsListModel(QObject *parent) : QAbstractListModel(parent)
{

}

//==============================================================================

int WalletTransactionsListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 0;
}

//==============================================================================

QVariant WalletTransactionsListModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

//==============================================================================

QHash<int, QByteArray> WalletTransactionsListModel::roleNames() const
{
    static QHash<int, QByteArray> result;
    if(result.isEmpty())
    {
    }

    return result;
}

//==============================================================================
