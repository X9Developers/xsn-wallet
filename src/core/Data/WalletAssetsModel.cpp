#include "WalletAssetsModel.hpp"

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
    using namespace bitcoin;
    addAsset(CoinAsset(384u, "Stakenet", "XSN",
                       CChainParams({
                                        { CChainParams::Base58Type::PUBKEY_ADDRESS, {76}},
                                        { CChainParams::Base58Type::SCRIPT_ADDRESS, {16}},
                                        { CChainParams::Base58Type::SECRET_KEY, {204}},
                                        { CChainParams::Base58Type::EXT_PUBLIC_KEY, {0x04, 0x88, 0xB2, 0x1E}},
                                        { CChainParams::Base58Type::EXT_SECRET_KEY, {0x04, 0x88, 0xAD, 0xE4}}
                                    })));
}

//==============================================================================

void WalletAssetsModel::addAsset(CoinAsset asset)
{
    _assets.emplace(asset.coinID, asset);
}

//==============================================================================
