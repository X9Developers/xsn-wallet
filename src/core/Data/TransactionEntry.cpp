#include "TransactionEntry.hpp"

//==============================================================================

TransactionEntry::TransactionEntry(QString txId, TransactionEntry::Type txType, int delta) :
    _transactionID(txId),
    _txType(txType),
    _delta(delta)
{

}

//==============================================================================
