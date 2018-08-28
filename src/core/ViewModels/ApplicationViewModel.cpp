#include "ApplicationViewModel.hpp"
#include "Models/EmulatorWalletDataSource.hpp"

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

WalletDataSource* ApplicationViewModel::dataSource()
{
    return _emulatorWalletDataSource.get();
}

//==============================================================================

void ApplicationViewModel::init()
{
    initDataSource();
}

//==============================================================================

void ApplicationViewModel::initDataSource()
{
    _emulatorWalletDataSource.reset(new EmulatorWalletDataSource());
}

//==============================================================================

