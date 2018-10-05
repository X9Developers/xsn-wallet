#include "TransactionEntry.hpp"

//==============================================================================

TransactionEntry::TransactionEntry(unsigned assetId, QString txId, TransactionEntry::Type txType, int delta, QDateTime txDate) :
    _assetID(assetId),
    _transactionID(txId),
    _txType(txType),
    _delta(delta),
    _transactionDate(txDate)
{

}

//==============================================================================
