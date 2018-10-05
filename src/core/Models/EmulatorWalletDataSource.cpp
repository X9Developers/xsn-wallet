#include "EmulatorWalletDataSource.hpp"
#include <map>
#include <algorithm>
#include <QDebug>

//==============================================================================

EmulatorWalletDataSource::EmulatorWalletDataSource(QObject *parent)
    : WalletDataSource{parent}
{
    init();
}

//==============================================================================

EmulatorWalletDataSource::~EmulatorWalletDataSource()
{

}

//==============================================================================

WalletDataSource::TransactionsList EmulatorWalletDataSource::executeFetch(AssetID id)
{
    auto it = _transactionMap.find(id);
    if(it != std::end(_transactionMap))
        return it->second;

    return TransactionsList();
}

//==============================================================================

WalletDataSource::TransactionsList EmulatorWalletDataSource::executeFetchAll()
{
    TransactionsList result;
    for(auto &&entry : _transactionMap)
    {
        const auto &list = entry.second;
        std::copy(std::begin(list), std::end(list), std::back_inserter(result));
    }

    return result;
}

//==============================================================================

static TransactionEntry GenerateTransaction()
{
    TransactionEntry::Type type;

    if(rand() % 2 == 1)
        type = TransactionEntry::Type::Sent;
    else
        type = TransactionEntry::Type::Received;

    return TransactionEntry(QString::number(rand() % 1000), type, rand() % 100, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
}

//==============================================================================

void EmulatorWalletDataSource::executeAdd(AssetID assetID, int count)
{
    int id = assetID;
    TransactionEntry transaction = GenerateTransaction();

    auto it = _transactionMap.find(id);
    if(it != std::end(_transactionMap))
    {
        for(int i = 0; i < count; ++i)
        {
            it->second.push_back(transaction);
            transactionAdded(assetID, transaction);
        }
    }
    else
    {
        qDebug() << "Transaction not added";
    }
}

//==============================================================================

void EmulatorWalletDataSource::clearTransactions(AssetID assetID)
{
    if(_transactionMap.count(assetID))
    {
        _transactionMap[assetID].clear();
        transactionsFetched(assetID, {});
    }
}

//==============================================================================

void EmulatorWalletDataSource::init()
{
    TransactionsList bitcoinTransactionList;
    bitcoinTransactionList.push_back(TransactionEntry("1", TransactionEntry::Type::Sent, 100, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    bitcoinTransactionList.push_back(TransactionEntry("2", TransactionEntry::Type::Received, 20, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    bitcoinTransactionList.push_back(TransactionEntry("3", TransactionEntry::Type::Sent, 133, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    bitcoinTransactionList.push_back(TransactionEntry("4", TransactionEntry::Type::Sent, 46, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));

    _transactionMap.emplace(0, bitcoinTransactionList);

    TransactionsList dashTransactionList;
    dashTransactionList.push_back(TransactionEntry("5", TransactionEntry::Type::Sent, 10, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    dashTransactionList.push_back(TransactionEntry("6", TransactionEntry::Type::Received, 18, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    dashTransactionList.push_back(TransactionEntry("7", TransactionEntry::Type::Sent, 32, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    dashTransactionList.push_back(TransactionEntry("8", TransactionEntry::Type::Sent, 14, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));

    _transactionMap.emplace(5, dashTransactionList);

    TransactionsList XSNTransactionList;
    XSNTransactionList.push_back(TransactionEntry("9", TransactionEntry::Type::Sent, 10, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    XSNTransactionList.push_back(TransactionEntry("10", TransactionEntry::Type::Received, 18, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    XSNTransactionList.push_back(TransactionEntry("11", TransactionEntry::Type::Sent, 32, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    XSNTransactionList.push_back(TransactionEntry("12", TransactionEntry::Type::Sent, 14, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));

    _transactionMap.emplace(384, XSNTransactionList);
}

//==============================================================================

