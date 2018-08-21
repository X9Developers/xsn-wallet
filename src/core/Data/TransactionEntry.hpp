#ifndef TRANSACTIONENTRY_HPP
#define TRANSACTIONENTRY_HPP

#include <QString>

struct TransactionEntry
{
    enum class Type {
        Received,
        Sent
    };

    TransactionEntry(QString txId, Type txType, int delta);

    const QString _transactionID;
    const Type _txType;
    const int _delta;
};

#endif // TRANSACTIONENTRY_HPP
