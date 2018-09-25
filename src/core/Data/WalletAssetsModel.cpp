#include "WalletAssetsModel.hpp"
#include <QFile>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

//==============================================================================

WalletAssetsModel::WalletAssetsModel(QObject *parent) : QObject(parent)
{
    init();
}

//==============================================================================

WalletAssetsModel::~WalletAssetsModel()
{

}

//==============================================================================

auto WalletAssetsModel::assets() const -> Assets
{
    Assets result;
    for(auto &&item : _assets)
        result.emplace_back(item.second);

    return result;
}

//==============================================================================

const CoinAsset &WalletAssetsModel::assetById(unsigned id) const
{
    return _assets.at(id);
}

//==============================================================================

void WalletAssetsModel::init()
{
    QFile file(":/data/assets_conf.json");

    if(file.open(QFile::ReadOnly))
    {
        auto doc = QJsonDocument::fromJson(file.readAll());
        for(QJsonValueRef object : doc.array())
        {
            addAsset(CoinAsset::FromJson(object.toObject()));
        }
    }
    else
    {
        qCritical() << "Failed to ope assets_conf.json";
    }
}

//==============================================================================

void WalletAssetsModel::addAsset(CoinAsset asset)
{
    _assets.emplace(asset.coinID, asset);
}

//==============================================================================
