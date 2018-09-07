#include "TransactionEntry.hpp"

//==============================================================================

TransactionEntry::TransactionEntry(QString txId, TransactionEntry::Type txType, int delta, QDateTime txDate) :
    _transactionID(txId),
    _txType(txType),
    _delta(delta),
    _transactionDate(txDate)
{

}

//==============================================================================
