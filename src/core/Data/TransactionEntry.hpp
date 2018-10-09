#ifndef TRANSACTIONENTRY_HPP
#define TRANSACTIONENTRY_HPP

#include <QString>
#include <QDateTime>
#include "Utils/Common.hpp"

struct TransactionEntry
{
    enum class Type {
        Received,
        Sent
    };

    TransactionEntry(AssetID assetId, QString txId, Type txType, int delta, QDateTime txDate);
    const AssetID _assetID;
    const QString _transactionID;
    const Type _txType;
    const int _delta;
    const QDateTime _transactionDate;
};

#endif // TRANSACTIONENTRY_HPP
