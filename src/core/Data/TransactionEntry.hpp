#ifndef TRANSACTIONENTRY_HPP
#define TRANSACTIONENTRY_HPP

#include <QString>
#include <QDateTime>

struct TransactionEntry
{
    enum class Type {
        Received,
        Sent
    };

    TransactionEntry(unsigned assetId, QString txId, Type txType, int delta, QDateTime txDate);
    const unsigned _assetID;
    const QString _transactionID;
    const Type _txType;
    const int _delta;
    const QDateTime _transactionDate;
};

#endif // TRANSACTIONENTRY_HPP
