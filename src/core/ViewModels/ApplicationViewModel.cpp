#include "ApplicationViewModel.hpp"
#include "Models/EmulatorWalletDataSource.hpp"
#include <Models/AllTransactionsDataSource.hpp>
#include <Models/WalletTransactionsListModel.hpp>
#include "Data/WalletAssetsModel.hpp"

//==============================================================================

ApplicationViewModel::ApplicationViewModel(QObject *parent) : QObject(parent)
{
    init();
}

//==============================================================================

ApplicationViewModel::~ApplicationViewModel()
{

}

//==============================================================================

WalletDataSource* ApplicationViewModel::dataSource() const
{
    return _emulatorWalletDataSource.data();
}

//==============================================================================

const WalletAssetsModel &ApplicationViewModel::assetsModel() const
{
    return *_walletAssetsModel;
}

//==============================================================================

ApplicationViewModel *ApplicationViewModel::Instance()
{
    static ApplicationViewModel instance;
    return &instance;
}

//==============================================================================

QObject *ApplicationViewModel::allTransactionsListModel() const
{
    return _allTransactionsListNodel.get();
}

//==============================================================================

void ApplicationViewModel::init()
{
    initWalletAssets();
    initDataSource();
    initAllTransactions();
}

//==============================================================================

void ApplicationViewModel::initDataSource()
{
    _emulatorWalletDataSource = new EmulatorWalletDataSource(_walletAssetsModel.get());
}

//==============================================================================

void ApplicationViewModel::initWalletAssets()
{
    _walletAssetsModel.reset(new WalletAssetsModel(":/data/assets_conf.json"));
}

//==============================================================================

void ApplicationViewModel::initAllTransactions()
{
    auto allTransactionsDataSource = new AllTransactionsDataSource(dataSource(), this);
    _allTransactionsListNodel.reset(new WalletTransactionsListModel(allTransactionsDataSource, _walletAssetsModel.get()));

    allTransactionChanged();
}

//==============================================================================

