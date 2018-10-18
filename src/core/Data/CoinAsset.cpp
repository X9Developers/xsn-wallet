#include "CoinAsset.hpp"

#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>

//==============================================================================

static bitcoin::CChainParams ChainParamsFromJson(QJsonObject obj)
{
    using namespace bitcoin;
    auto base58Prefixes = obj.value("base58Prefix").toObject();

    const std::map<std::string, CChainParams::Base58Type> mapping {
        { "pubkeyAddress", CChainParams::Base58Type::PUBKEY_ADDRESS },
        { "scriptAddress", CChainParams::Base58Type::SCRIPT_ADDRESS },
        { "secretKey", CChainParams::Base58Type::SECRET_KEY },
        { "extPublicKey", CChainParams::Base58Type::EXT_PUBLIC_KEY },
        { "extSecretKey", CChainParams::Base58Type::EXT_SECRET_KEY }
    };

    CChainParams::Base58TypesMap typesMap;
    for(auto &&key : base58Prefixes.keys())
    {
        if(mapping.count(key.toStdString()))
        {
            std::vector<unsigned char> bytes;
            for(QJsonValueRef byte : base58Prefixes.value(key).toArray())
            {
                bytes.emplace_back(byte.toInt());
            }
            typesMap.emplace(mapping.at(key.toStdString()), bytes);
        }
    }

    return CChainParams(typesMap);
}

//==============================================================================

CoinAsset::CoinAsset(unsigned int coinID, QString name, QString ticket, bitcoin::CChainParams params, Misc data) :
    _coinID(coinID),
    _name(name),
    _ticket(ticket),
    _params(params),
    _misc(data)
{

}

//==============================================================================

CoinAsset CoinAsset::FromJson(const QJsonObject &obj)
{
    return CoinAsset(static_cast<unsigned>(obj.value("id").toInt()),
                     obj.value("name").toString(),
                     obj.value("symbol").toString(),
                     ChainParamsFromJson(obj.value("chainparams").toObject()),
                     Misc::FromJson(obj.value("misc").toObject()));
}

//==============================================================================

void CoinAsset::setCoinID(unsigned int coinID)
{
    _coinID = coinID;
}

//==============================================================================

unsigned int CoinAsset::coinID() const
{
    return _coinID;
}

//==============================================================================

void CoinAsset::setName(QString name)
{
    _name = name;
}

//==============================================================================

QString CoinAsset::name() const
{
    return _name;
}

//==============================================================================

void CoinAsset::setTicket(QString ticket)
{
    _ticket = ticket;
}

//==============================================================================

QString CoinAsset::ticket() const
{
    return _ticket;
}

//==============================================================================

void CoinAsset::setParams(bitcoin::CChainParams params)
{
    _params = params;
}

//==============================================================================

bitcoin::CChainParams CoinAsset::params() const
{
    return _params;
}

//==============================================================================

void CoinAsset::setMisc(CoinAsset::Misc misc)
{
    _misc = misc;
}

//==============================================================================

CoinAsset::Misc CoinAsset::misc() const
{
    return _misc;
}

//==============================================================================

CoinAsset::Misc::Misc(QString color) :
    color(color)
{

}

//==============================================================================

CoinAsset::Misc CoinAsset::Misc::FromJson(const QJsonObject &obj)
{
    return Misc(obj.value("color").toString());
}

//==============================================================================
