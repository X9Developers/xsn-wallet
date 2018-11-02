#include "CurrencyModel.hpp"
#include <QDebug>

//==============================================================================

CurrencyModel::CurrencyModel(QObject *parent): QAbstractListModel(parent)
{

}

//==============================================================================

CurrencyModel::~CurrencyModel()
{

}

//==============================================================================

int CurrencyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(_currencies.size());
}

//==============================================================================

QVariant CurrencyModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= rowCount(QModelIndex()))
    {
        return QVariant();
    }

    const auto currency = _currencies.at(static_cast<size_t>(index.row()));

    switch(role) {
    case SymbolRole: return currency.first;
    case NameRole: return currency.second;
    default:
        break;
    }

    return QVariant();
}

//==============================================================================

QHash<int, QByteArray> CurrencyModel::roleNames() const
{
    static QHash<int, QByteArray> roles;

    if(roles.empty())
    {
        roles[SymbolRole] = "symbol";
        roles[NameRole] = "name";
    }

    return roles;

}

//==============================================================================

