#include "CoinAsset.hpp"

//==============================================================================

CoinAsset::CoinAsset(unsigned int coinID, QString name, QString ticket, bitcoin::CChainParams params) :
    coinID(coinID),
    name(name),
    ticket(ticket),
    params(params)
{

}

//==============================================================================
