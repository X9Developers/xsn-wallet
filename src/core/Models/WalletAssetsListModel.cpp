#include "WalletAssetsListModel.hpp"
#include <ViewModels/ApplicationViewModel.hpp>
#include <Data/WalletAssetsModel.hpp>
#include <Data/AssetsBalance.hpp>
#include <Data/WalletAssetsModel.hpp>
#include <Data/CoinAsset.hpp>
#include <QDebug>

//==============================================================================

struct WalletAssetsListModel::WalletAssetsListModelImpl {
    std::vector<CoinAsset> _assets;
    AssetsBalance::BalanceMap _assetBalance;
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

    switch(role) {
    case IDRole: return asset.coinID();
    case NameRole: return asset.name();
    case TicketRole: return asset.ticket();
    case ColorRole: return asset.misc().color;
    case BalanceRole: return QVariant::fromValue(getAssetBalance(asset.coinID()));
    case PortfolioPercentageRole: return 0; //QVariant::fromValue(getAssetBalance(asset.coinID()) / _balanceSum  * 100);
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
        roles[PortfolioPercentageRole] = "percent";
    }

    return roles;
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

    _assetBalance = assetsBalance;

    _impl->_assetBalance = assetsBalance->balance();
    _balanceSum = assetsBalance->balanceSum();

    connect(assetsBalance, &AssetsBalance::balanceUpdated, this, &WalletAssetsListModel::onAssetBalanceUpdated);

    sortByColumn("Balance");

    endResetModel();
}

//==============================================================================

Balance WalletAssetsListModel::getAssetBalance(AssetID assetID) const
{
    return _impl->_assetBalance.find(assetID) != _impl->_assetBalance.end() ?
                _impl->_assetBalance.at(assetID) : 0;
}

//==============================================================================

void WalletAssetsListModel::sortByColumn(QString columnName)
{
    beginResetModel();

    if(columnName == "Balance")
    {
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
    _impl->_assetBalance = _assetBalance->balance();
    _balanceSum = _assetBalance->balanceSum();
    endResetModel();
}
//==============================================================================
