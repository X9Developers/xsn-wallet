#include "EmulatorWalletDataSource.hpp"
#include "ViewModels/ApplicationViewModel.hpp"
#include "Data/WalletAssetsModel.hpp"
#include <map>
#include <algorithm>
#include <QDebug>

//==============================================================================

EmulatorWalletDataSource::EmulatorWalletDataSource(QPointer<WalletAssetsModel> walletAssetsModel, QObject *parent) :
    WalletDataSource{parent},
  _walletAssetsModel(walletAssetsModel)
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

static TransactionEntry GenerateTransaction(AssetID assetID)
{
    TransactionEntry::Type type;

    if(rand() % 2 == 1)
        type = TransactionEntry::Type::Sent;
    else
        type = TransactionEntry::Type::Received;

    return TransactionEntry(assetID, QString::number(rand() % 1000), type, rand() % 100, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0)));
}

//==============================================================================

void EmulatorWalletDataSource::executeAdd(AssetID assetID, int count)
{
    AssetID id = assetID;
    TransactionEntry transaction = GenerateTransaction(assetID);

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
    auto assetsModel = _walletAssetsModel->assets();

    TransactionsList bitcoinTransactionList;
    bitcoinTransactionList.push_back(TransactionEntry(assetsModel.at(0).coinID(), "1", TransactionEntry::Type::Sent, 100, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    bitcoinTransactionList.push_back(TransactionEntry(assetsModel.at(0).coinID(), "2", TransactionEntry::Type::Received, 20, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    bitcoinTransactionList.push_back(TransactionEntry(assetsModel.at(0).coinID(), "3", TransactionEntry::Type::Sent, 133, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    bitcoinTransactionList.push_back(TransactionEntry(assetsModel.at(0).coinID(), "4", TransactionEntry::Type::Sent, 46, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));

    _transactionMap.emplace(assetsModel.at(0).coinID(), bitcoinTransactionList);

    TransactionsList dashTransactionList;
    dashTransactionList.push_back(TransactionEntry(assetsModel.at(1).coinID(), "5", TransactionEntry::Type::Sent, 10, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    dashTransactionList.push_back(TransactionEntry(assetsModel.at(1).coinID(), "6", TransactionEntry::Type::Received, 18, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    dashTransactionList.push_back(TransactionEntry(assetsModel.at(1).coinID(), "7", TransactionEntry::Type::Sent, 32, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    dashTransactionList.push_back(TransactionEntry(assetsModel.at(1).coinID(), "8", TransactionEntry::Type::Sent, 14, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));

    _transactionMap.emplace(assetsModel.at(1).coinID(), dashTransactionList);

    TransactionsList XSNTransactionList;
    XSNTransactionList.push_back(TransactionEntry(assetsModel.at(2).coinID(), "9", TransactionEntry::Type::Sent, 10, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    XSNTransactionList.push_back(TransactionEntry(assetsModel.at(2).coinID(), "10", TransactionEntry::Type::Received, 18, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    XSNTransactionList.push_back(TransactionEntry(assetsModel.at(2).coinID(), "11", TransactionEntry::Type::Sent, 32, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));
    XSNTransactionList.push_back(TransactionEntry(assetsModel.at(2).coinID(), "12", TransactionEntry::Type::Sent, 14, QDateTime(QDate(2012, 7, 6), QTime(8, 30, 0))));

    _transactionMap.emplace(assetsModel.at(2).coinID(), XSNTransactionList);
}

//==============================================================================

