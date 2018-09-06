#ifndef EMULATORVIEWMODEL_HPP
#define EMULATORVIEWMODEL_HPP

#include <QObject>
#include <memory>
#include <QPointer>

class WalletDataSource;
class ApplicationViewModel;
class EmulatorWalletDataSource;

class EmulatorViewModel : public QObject
{
    Q_OBJECT

public:
    EmulatorViewModel(QObject *parent = nullptr);
    ~EmulatorViewModel();
signals:
    void applicationViewModelChanged();

public slots:
    void addTransaction(QString currentModel);
    void initialize(ApplicationViewModel *applicationViewModel);

private:
    QPointer<EmulatorWalletDataSource> _walletDataSource;
};

#endif // EMULATORVIEWMODEL_HPP
