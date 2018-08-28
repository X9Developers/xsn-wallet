#include "EmulatorWalletDataSource.hpp"
#include <QDebug>
#include <map>

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

WalletDataSource::TransactionsList EmulatorWalletDataSource::executeFetch(QString id)
{
    qDebug() << "Coin`s ID:" << id;
    auto it = _transactionMap.find(id);
    return it->second;
}

//==============================================================================

void EmulatorWalletDataSource::init()
{
    TransactionsList bitcoinTransactionList;
    bitcoinTransactionList.push_back(TransactionEntry("1", TransactionEntry::Type::Sent, 100));
    bitcoinTransactionList.push_back(TransactionEntry("2", TransactionEntry::Type::Received, 20));
    bitcoinTransactionList.push_back(TransactionEntry("3", TransactionEntry::Type::Sent, 133));
    bitcoinTransactionList.push_back(TransactionEntry("4", TransactionEntry::Type::Sent, 46));

    _transactionMap.emplace("Bitcoin", bitcoinTransactionList);

    TransactionsList dashTransactionList;
    dashTransactionList.push_back(TransactionEntry("5", TransactionEntry::Type::Sent, 10));
    dashTransactionList.push_back(TransactionEntry("6", TransactionEntry::Type::Received, 18));
    dashTransactionList.push_back(TransactionEntry("7", TransactionEntry::Type::Sent, 32));
    dashTransactionList.push_back(TransactionEntry("8", TransactionEntry::Type::Sent, 14));

    _transactionMap.emplace("Dash", dashTransactionList);

    TransactionsList XSNTransactionList;
    XSNTransactionList.push_back(TransactionEntry("9", TransactionEntry::Type::Sent, 10));
    XSNTransactionList.push_back(TransactionEntry("10", TransactionEntry::Type::Received, 18));
    XSNTransactionList.push_back(TransactionEntry("11", TransactionEntry::Type::Sent, 32));
    XSNTransactionList.push_back(TransactionEntry("12", TransactionEntry::Type::Sent, 14));

    _transactionMap.emplace("XSN", XSNTransactionList);
}

//==============================================================================


