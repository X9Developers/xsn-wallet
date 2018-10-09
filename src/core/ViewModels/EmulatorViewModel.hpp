#ifndef EMULATORVIEWMODEL_HPP
#define EMULATORVIEWMODEL_HPP

#include <QObject>
#include <memory>
#include <QPointer>
#include "Utils/Common.hpp"

class WalletDataSource;
class ApplicationViewModel;
class EmulatorWalletDataSource;

class EmulatorViewModel : public QObject
{
    Q_OBJECT

public:
    EmulatorViewModel(QObject *parent = nullptr);
    ~EmulatorViewModel();

public slots:
    void addTransaction(AssetID currentModel, int count);
    void clearTransactions(AssetID currentModel);
    void initialize(ApplicationViewModel *applicationViewModel);

private:
    QPointer<EmulatorWalletDataSource> _walletDataSource;
};

#endif // EMULATORVIEWMODEL_HPP
