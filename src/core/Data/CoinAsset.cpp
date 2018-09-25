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

CoinAsset::CoinAsset(unsigned int coinID, QString name, QString ticket, bitcoin::CChainParams params) :
    coinID(coinID),
    name(name),
    ticket(ticket),
    params(params)
{

}

//==============================================================================

CoinAsset CoinAsset::FromJson(const QJsonObject &obj)
{
    return CoinAsset(static_cast<unsigned>(obj.value("id").toInt()),
                     obj.value("name").toString(),
                     obj.value("symbol").toString(),
                     ChainParamsFromJson(obj.value("chainparams").toObject()));
}

//==============================================================================
