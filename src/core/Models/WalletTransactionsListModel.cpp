#include "WalletTransactionsListModel.hpp"
#include "Data/TransactionEntry.hpp"

//==============================================================================

WalletTransactionsListModel::WalletTransactionsListModel(QPointer<WalletDataSource> dataSource, QString assetID, QObject *parent) :
    QAbstractListModel(parent),
    _walletDataSource(dataSource),
    _assetID(assetID)
{
    init();
}

//==============================================================================

WalletTransactionsListModel::~WalletTransactionsListModel()
{

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
    case TxDateRole: return transaction._transactionDate.toString("MMM\ndd");
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
        roleNames[Roles::TxDateRole] = "txDate";
    }
    return roleNames;
}

//==============================================================================

void WalletTransactionsListModel::onTransactionFetched(QString assetID, WalletDataSource::TransactionsList list)
{
    if(assetID != _assetID)
    {
        return;
    }

    beginResetModel();
    _transactionList.swap(list);
    endResetModel();
}

//==============================================================================

void WalletTransactionsListModel::init()
{
    if(_walletDataSource)
    {
        connect(_walletDataSource.data(), &WalletDataSource::transactionsFetched, this, &WalletTransactionsListModel::onTransactionFetched);
        _walletDataSource->fetchTransactions(_assetID);
    }
}

//==============================================================================

