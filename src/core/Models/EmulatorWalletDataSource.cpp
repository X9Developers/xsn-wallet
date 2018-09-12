#include "EmulatorWalletDataSource.hpp"
#include <map>
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

WalletDataSource::TransactionsList EmulatorWalletDataSource::executeFetch(QString id)
{
    auto it = _transactionMap.find(id);
    if(it != std::end(_transactionMap))
        return it->second;

    return TransactionsList();
}

//==============================================================================

static TransactionEntry GenerateTransaction()
{
    TransactionEntry::Type type;

    if(rand() % 2 == 1)
        type = TransactionEntry::Type::Sent;
    else
        type = TransactionEntry::Type::Received;

    return TransactionEntry(QString::number(rand() % 1000), type, rand() % 100);
}

//==============================================================================

void EmulatorWalletDataSource::executeAdd(QString modelName)
{
    srand (time(0));

    QString id = modelName;
    TransactionEntry transaction = GenerateTransaction();

    auto it = _transactionMap.find(id);
    if(it != std::end(_transactionMap))
    {
        for(auto trans : it->second)
        {
            if(trans._transactionID == transaction._transactionID)
                return;
        }

        it->second.push_back(transaction);
        transactionsFetched(modelName, it->second);
    }
    else
        qDebug() << "Transaction not added";
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

