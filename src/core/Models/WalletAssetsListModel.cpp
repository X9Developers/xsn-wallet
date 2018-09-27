#include "WalletAssetsListModel.hpp"
#include <ViewModels/ApplicationViewModel.hpp>
#include <Data/WalletAssetsModel.hpp>
#include <Data/CoinAsset.hpp>
#include <QDebug>

//==============================================================================

struct WalletAssetsListModel::WalletAssetsListModelImpl {
    std::vector<CoinAsset> _assets;
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
    case IDRole: return asset.coinID;
    case NameRole: return asset.name;
    case TicketRole: return asset.ticket;
    case ColorRole: return asset.misc.color;
    case ButtonColorRole: return asset.misc.buttonColor;
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
        roles[ButtonColorRole] = "buttonColor";
    }

    return roles;
}

//==============================================================================

void WalletAssetsListModel::initialize(QObject *appViewModel)
{
    if(auto viewModel = qobject_cast<ApplicationViewModel*>(appViewModel))
    {
        initAssets(viewModel->assetsModel());
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
    _impl->_assets = assetModel.assets();
    endResetModel();
}

//==============================================================================
