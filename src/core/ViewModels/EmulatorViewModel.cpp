#include "EmulatorViewModel.hpp"
#include "Models/EmulatorWalletDataSource.hpp"
#include "ViewModels/ApplicationViewModel.hpp"

//==============================================================================

EmulatorViewModel::EmulatorViewModel(QObject *parent)
{

}

//==============================================================================

EmulatorViewModel::~EmulatorViewModel()
{

}

//==============================================================================

void EmulatorViewModel::setApplicationViewModel(ApplicationViewModel *applicationViewModel)
{
   _walletDataSource = applicationViewModel->dataSource();
}

//==============================================================================

void EmulatorViewModel::addTransaction()
{
    if(_walletDataSource)
        dynamic_cast<EmulatorWalletDataSource*>(_walletDataSource.data())->executeAdd();
}

//==============================================================================

