#include "EmulatorViewModel.hpp"
#include "Models/EmulatorWalletDataSource.hpp"
#include "ViewModels/ApplicationViewModel.hpp"

//==============================================================================

EmulatorViewModel::EmulatorViewModel(QObject *parent) : QObject(parent)
{

}

//==============================================================================

EmulatorViewModel::~EmulatorViewModel()
{

}

//==============================================================================

void EmulatorViewModel::clearTransactions(QString currentModel)
{
    if(_walletDataSource)
    {
        _walletDataSource->clearTransactions(currentModel);
    }
}

//==============================================================================

void EmulatorViewModel::initialize(ApplicationViewModel *applicationViewModel)
{
    _walletDataSource = qobject_cast<EmulatorWalletDataSource*>(applicationViewModel->dataSource());
}

//==============================================================================

void EmulatorViewModel::addTransaction(QString currentModel, int count)
{
    if(_walletDataSource)
    {
        _walletDataSource->executeAdd(currentModel, count);
    }
}

//==============================================================================

