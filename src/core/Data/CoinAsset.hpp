#ifndef COINASSET_HPP
#define COINASSET_HPP

#include <QString>
#include <chainparams.hpp>

class QJsonObject;

struct CoinAsset
{
    struct Misc {

        Misc(QString color);
        static Misc FromJson(const QJsonObject &obj);

        const QString color;
    };


    CoinAsset(unsigned int coinID, QString name,
              QString ticket, bitcoin::CChainParams params, Misc misc);


    static CoinAsset FromJson(const QJsonObject &obj);

    const unsigned int coinID;
    const QString name;
    const QString ticket;
    const bitcoin::CChainParams params;
    const Misc misc;
};

#endif // COINASSET_HPP
