#include "WalletTransactionsListModel.hpp"
#include "Data/TransactionEntry.hpp"

//==============================================================================

WalletTransactionsListModel::WalletTransactionsListModel(std::weak_ptr<WalletDataSource> dataSource, QString coinsID, QObject *parent) :
    QAbstractListModel(parent),
    _walletDataSource(dataSource),
    _coinsID(coinsID)
{
    init();
}

//==============================================================================

int WalletTransactionsListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _transactionList.size();
}

//==============================================================================

QVariant WalletTransactionsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const int row = index.row();
    const TransactionEntry transaction = _transactionList.at(row);
    switch(role)
    {
    case TransactionIDRole: return transaction._transactionID;
    case IsSendRole: return transaction._txType == TransactionEntry::Type::Sent;
    case DeltaRole: return transaction._delta;
    case ImageUrlRole: return "";
    }

    return QVariant();
}

//==============================================================================

QHash<int, QByteArray> WalletTransactionsListModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames;
    if(roleNames.isEmpty())
    {
        roleNames[Roles::TransactionIDRole] = "id";
        roleNames[Roles::IsSendRole] = "isSend";
        roleNames[Roles::DeltaRole] = "delta";
        roleNames[Roles::ImageUrlRole] = "imageUrl";
    }
    return roleNames;
}

//==============================================================================

void WalletTransactionsListModel::onTransactionFetched(WalletDataSource::TransactionsList list)
{
    beginResetModel();
    for(auto transaction : list )
        _transactionList.push_back(transaction);
    endResetModel();
}

//==============================================================================

void WalletTransactionsListModel::init()
{
    if(auto dataSource = _walletDataSource.lock())
    {
        connect(dataSource.get(), &WalletDataSource::transactionsFetched, this, &WalletTransactionsListModel::onTransactionFetched);
        dataSource->fetchTransactions(_coinsID);
    }
}

//==============================================================================

