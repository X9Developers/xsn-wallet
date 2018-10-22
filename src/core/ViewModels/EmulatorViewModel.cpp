#include "EmulatorViewModel.hpp"
#include "Models/EmulatorWalletDataSource.hpp"
#include "ViewModels/ApplicationViewModel.hpp"
#include <QDebug>

//==============================================================================

EmulatorViewModel::EmulatorViewModel(QObject *parent) : QObject(parent)
{

}

//==============================================================================

EmulatorViewModel::~EmulatorViewModel()
{

}

//==============================================================================

void EmulatorViewModel::clearTransactions(AssetID currentModel)
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

void EmulatorViewModel::addTransaction(AssetID currentModel, int count)
{
    if(_walletDataSource)
    {
        _walletDataSource->executeAdd(currentModel, count);
        qDebug() << "addTransaction"  << currentModel;
    }
}

//==============================================================================

