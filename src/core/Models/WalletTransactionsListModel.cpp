#include "WalletTransactionsListModel.hpp"
#include "Data/TransactionEntry.hpp"
#include "TransactionsDataSource.hpp"
#include "Data/WalletAssetsModel.hpp"

//==============================================================================

WalletTransactionsListModel::WalletTransactionsListModel(QPointer<TransactionsDataSource> dataSource,
                                                         QPointer<const WalletAssetsModel> walletAssetsModel,
                                                         QObject *parent) :
    QAbstractListModel(parent),
    _dataSource(dataSource),
    _walletAssetsModel(walletAssetsModel)
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
    return static_cast<int>(_transactionList.size());
}

//==============================================================================

QVariant WalletTransactionsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const size_t row = static_cast<size_t>(index.row());
    const TransactionEntry transaction = _transactionList.at(row);
    switch(role)
    {
    case TransactionIDRole: return transaction._transactionID;
    case IsSendRole: return transaction._txType == TransactionEntry::Type::Sent;
    case DeltaRole: return transaction._delta;
    case ImageUrlRole: return "";
    case TxDateRole: return transaction._transactionDate.toString("yyyy.MM.dd hh:mm");
    case CurrencyRole: return _walletAssetsModel.data()->assetById(transaction._assetID).name;
    case SymbolRole:return _walletAssetsModel.data()->assetById(transaction._assetID).ticket;
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
        roleNames[Roles::CurrencyRole] = "currency";
        roleNames[Roles::SymbolRole] = "symbol";
    }
    return roleNames;
}

//==============================================================================

void WalletTransactionsListModel::onTransactionFetched(WalletDataSource::TransactionsList list)
{
    beginResetModel();
    _transactionList.swap(list);
    endResetModel();
}

//==============================================================================

void WalletTransactionsListModel::onTransactionAdded(TransactionEntry entry)
{
    int rows = rowCount(QModelIndex());
    beginInsertRows(QModelIndex(), rows, rows);
    _transactionList.emplace_back(entry);
    endInsertRows();
}

//==============================================================================

void WalletTransactionsListModel::init()
{
    if(_dataSource)
    {
        connect(_dataSource, &TransactionsDataSource::transactionsFetched,
                this, &WalletTransactionsListModel::onTransactionFetched);
        connect(_dataSource, &TransactionsDataSource::transactionAdded,
                this, &WalletTransactionsListModel::onTransactionAdded);
        _dataSource->fetchTransactions();
    }
}

//==============================================================================

