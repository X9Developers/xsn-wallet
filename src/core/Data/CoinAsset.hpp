#ifndef COINASSET_HPP
#define COINASSET_HPP

#include <QString>
#include <chainparams.hpp>

struct CoinAsset
{
    CoinAsset(unsigned int coinID, QString name,
              QString ticket, bitcoin::CChainParams params);

    const unsigned int coinID;
    const QString name;
    const QString ticket;
    const bitcoin::CChainParams params;
};

#endif // COINASSET_HPP
