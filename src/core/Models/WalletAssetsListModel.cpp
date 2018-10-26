#include "WalletAssetsListModel.hpp"
#include <ViewModels/ApplicationViewModel.hpp>
#include <Data/WalletAssetsModel.hpp>
#include <Data/AssetsBalance.hpp>
#include <Data/WalletAssetsModel.hpp>
#include <Data/CoinAsset.hpp>
#include <QDebug>
#include <numeric>

//==============================================================================

struct WalletAssetsListModel::WalletAssetsListModelImpl {
    std::vector<CoinAsset> _assets;
    AssetsBalance::BalanceMap _balance;
};

//==============================================================================

WalletAssetsListModel::WalletAssetsListModel(QObject *parent) :
    QAbstractListModel(parent),
    _impl(new WalletAssetsListModelImpl)
{
}

//==============================================================================

WalletAssetsListModel::~WalletAssetsListModel()
{

}

//==============================================================================

int WalletAssetsListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(_impl->_assets.size());
}

//==============================================================================

QVariant WalletAssetsListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= rowCount(QModelIndex()))
    {
        return QVariant();
    }
    const auto &asset = _impl->_assets.at(static_cast<size_t>(index.row()));
    Balance balance = getAssetBalance(asset.coinID());

    switch(role) {
    case IDRole: return asset.coinID();
    case NameRole: return asset.name();
    case TicketRole: return asset.ticket();
    case ColorRole: return asset.misc().color;
    case BalanceRole: return QVariant::fromValue(balance);
    case UsdBalanceRole: return QVariant::fromValue(getUsdBalance(asset.coinID(), balance));
    case PortfolioPercentageRole: return getPortfolioPercentage(balance);
    default:
        break;
    }

    return QVariant();
}

//==============================================================================

QHash<int, QByteArray> WalletAssetsListModel::roleNames() const
{
    static QHash<int, QByteArray> roles;

    if(roles.empty())
    {
        roles[IDRole] = "id";
        roles[NameRole] = "name";
        roles[TicketRole] = "symbol";
        roles[ColorRole] = "color";
        roles[BalanceRole] = "balance";
        roles[UsdBalanceRole] = "usdBalance";
        roles[PortfolioPercentageRole] = "percent";
    }

    return roles;
}

//==============================================================================

int WalletAssetsListModel::count() const
{
    return static_cast<int>(_impl->_assets.size());
}

//==============================================================================

QVariant WalletAssetsListModel::accountBalance() const
{
    return QVariant::fromValue(std::accumulate(std::begin(_impl->_balance), std::end(_impl->_balance), 0, [] (Balance value, const std::map<AssetID, Balance>::value_type& pair)
    {
       return value + pair.second;
    }));
}

//==============================================================================

void WalletAssetsListModel::initialize(QObject *appViewModel)
{
    if(auto viewModel = qobject_cast<ApplicationViewModel*>(appViewModel))
    {
        initAssets(viewModel->assetsModel());
        initBalance(viewModel->assetsBalance());
    }
    else
    {
        qWarning() << "No ApplicationViewModel, something is wrong, got instead:" << appViewModel;
    }
}

//==============================================================================

void WalletAssetsListModel::initAssets(const WalletAssetsModel &assetModel)
{
    beginResetModel();
    _impl->_assets =  assetModel.assets();
    endResetModel();
}

//==============================================================================

void WalletAssetsListModel::initBalance(AssetsBalance *assetsBalance)
{
    beginResetModel();
    _balanceSum = 0;

    _balance = assetsBalance;

    _impl->_balance = assetsBalance->balance();
    _balanceSum = assetsBalance->balanceSum();

    connect(assetsBalance, &AssetsBalance::balanceUpdated, this, &WalletAssetsListModel::onAssetBalanceUpdated);
    endResetModel();

    accountBalanceChanged();
}

//==============================================================================

Balance WalletAssetsListModel::getAssetBalance(AssetID assetID) const
{
    return _impl->_balance.find(assetID) != _impl->_balance.end() ?
                _impl->_balance.at(assetID) : 0;
}

//==============================================================================

Balance WalletAssetsListModel::getUsdBalance(AssetID assetID, Balance coinBalance) const
{
    // not implemented - only example
    return  (assetID + 2) * coinBalance;
}

//==============================================================================

int WalletAssetsListModel::getPortfolioPercentage(Balance balance) const
{
    return _balanceSum != 0 ? static_cast<int>(balance * 100 / _balanceSum) : 0;
}

//==============================================================================

void WalletAssetsListModel::sortByColumn(QString columnName)
{
    beginResetModel();

    if(columnName == "Balance")
    {
        std::multimap<Balance, CoinAsset> assetsVector;
        for(auto coinAsset : _impl->_assets)
            assetsVector.insert({ _impl->_balance.at(coinAsset.coinID()), coinAsset});

        std::vector<CoinAsset> sortedAssets;
        for(auto asset : assetsVector)
            sortedAssets.push_back(asset.second);

        _impl->_assets.swap(sortedAssets);
    }

    else if (columnName == "Currency")
    {
        std::sort(std::begin(_impl->_assets), std::end(_impl->_assets),[]( const CoinAsset &left, const CoinAsset &right)
        {
            return left.name() < right.name();
        });
    }

    endResetModel();
}

//==============================================================================

void WalletAssetsListModel::onAssetBalanceUpdated()
{
    beginResetModel();
    _impl->_balance = _balance->balance();
    _balanceSum = _balance->balanceSum();
    endResetModel();

    accountBalanceChanged();
}
//==============================================================================
