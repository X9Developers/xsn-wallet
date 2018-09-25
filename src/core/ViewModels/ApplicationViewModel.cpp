#include "ApplicationViewModel.hpp"
#include "Models/EmulatorWalletDataSource.hpp"
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

void ApplicationViewModel::init()
{
    initDataSource();
    initWalletAssets();
}

//==============================================================================

void ApplicationViewModel::initDataSource()
{
    _emulatorWalletDataSource = new EmulatorWalletDataSource();
}

//==============================================================================

void ApplicationViewModel::initWalletAssets()
{
    _walletAssetsModel.reset(new WalletAssetsModel);
}

//==============================================================================

