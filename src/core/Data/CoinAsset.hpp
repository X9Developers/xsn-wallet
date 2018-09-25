#ifndef COINASSET_HPP
#define COINASSET_HPP

#include <QString>
#include <chainparams.hpp>

class QJsonObject;

struct CoinAsset
{
    CoinAsset(unsigned int coinID, QString name,
              QString ticket, bitcoin::CChainParams params);

    static CoinAsset FromJson(const QJsonObject &obj);

    const unsigned int coinID;
    const QString name;
    const QString ticket;
    const bitcoin::CChainParams params;
};

#endif // COINASSET_HPP
