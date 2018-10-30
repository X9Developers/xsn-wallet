#include "AssetsListProxyModel.hpp"

//==============================================================================

AssetsListProxyModel::AssetsListProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    connect(this, &QSortFilterProxyModel::rowsInserted, this, &AssetsListProxyModel::countChanged);
    connect(this, &QSortFilterProxyModel::rowsRemoved, this, &AssetsListProxyModel::countChanged);
}

//==============================================================================

QObject *AssetsListProxyModel::source() const
{
    return sourceModel();
}

//==============================================================================

void AssetsListProxyModel::setSource(QObject *source)
{
    setSourceModel(qobject_cast<QAbstractItemModel *>(source));
}

//==============================================================================

QByteArray AssetsListProxyModel::filterRole() const
{
    return _filterRole;
}

//==============================================================================

void AssetsListProxyModel::setFilterRole(const QByteArray &role)
{
    if (_filterRole != role)
    {
        _filterRole = role;
        QSortFilterProxyModel::setFilterRole(roleKey(role));
    }
}

//==============================================================================

QString AssetsListProxyModel::filterString() const
{
    return filterRegExp().pattern();
}

//==============================================================================

void AssetsListProxyModel::setFilterString(const QString &filter)
{
    setFilterRegExp(QRegExp(filter, filterCaseSensitivity(), static_cast<QRegExp::PatternSyntax>(filterRegExp().patternSyntax())));
}

//==============================================================================

QByteArray AssetsListProxyModel::sortRole() const
{
    return _sortRole;
}

//==============================================================================

void AssetsListProxyModel::setSortRole(const QByteArray &role)
{
    if (_sortRole != role)
    {
        _sortRole = role;
        QSortFilterProxyModel::setSortRole(roleKey(role));
        sort(0);
    }
}

//==============================================================================

int AssetsListProxyModel::count() const
{
    return rowCount();
}

//==============================================================================

int AssetsListProxyModel::roleKey(const QByteArray &role) const
{
    QHash<int, QByteArray> roles = roleNames();
    QHashIterator<int, QByteArray> it(roles);
    while (it.hasNext())
    {
        it.next();
        if (it.value() == role)
            return it.key();
    }
    return -1;
}

//==============================================================================

bool AssetsListProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QRegExp rx = filterRegExp();
    if (rx.isEmpty())
        return true;
    QAbstractItemModel *model = sourceModel();
    if (filterRole().isEmpty()) {
        QHash<int, QByteArray> roles = roleNames();
        QHashIterator<int, QByteArray> it(roles);
        while (it.hasNext()) {
            it.next();
            QModelIndex sourceIndex = model->index(sourceRow, 0, sourceParent);
            QString key = model->data(sourceIndex, it.key()).toString();
            if (key.contains(rx))
                return true;
        }
        return false;
    }
    else
        return false;
}

//==============================================================================

bool AssetsListProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    return left.data(roleKey(_sortRole)) < right.data(roleKey(_sortRole));
}

//==============================================================================
