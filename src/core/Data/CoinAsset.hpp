#ifndef COINASSET_HPP
#define COINASSET_HPP

#include <QString>
#include <chainparams.hpp>
#include "Utils/Common.hpp"

class QJsonObject;

struct CoinAsset
{
    struct Misc {

        Misc(QString color);
        static Misc FromJson(const QJsonObject &obj);

        QString color;
    };


    CoinAsset(unsigned int coinID, QString name,
              QString ticket, bitcoin::CChainParams params, Misc misc);

    static CoinAsset FromJson(const QJsonObject &obj);

    unsigned int coinID() const;

    void setName(QString name);
    QString name() const;

    void setTicket(QString ticket);
    QString ticket() const;

    void setParams(bitcoin::CChainParams params);
    bitcoin::CChainParams params() const;

    void setMisc(Misc misc);
    Misc misc() const;


private:
    AssetID _coinID;
    QString _name;
    QString _ticket;
    bitcoin::CChainParams _params;
    Misc _misc;
};

#endif // COINASSET_HPP
