#ifndef EMULATORVIEWMODEL_HPP
#define EMULATORVIEWMODEL_HPP

#include <QObject>
#include <memory>
#include <QPointer>

class WalletDataSource;
class ApplicationViewModel;

class EmulatorViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ApplicationViewModel* applicationViewModel WRITE setApplicationViewModel NOTIFY applicationViewModelChanged)

public:
    EmulatorViewModel(QObject *parent = nullptr);
    ~EmulatorViewModel();

    void setApplicationViewModel(ApplicationViewModel* applicationViewModel);

signals:
    void applicationViewModelChanged();

public slots:
    void addTransaction(QString currentModel);

private:
    QPointer<WalletDataSource> _walletDataSource;
};

#endif // EMULATORVIEWMODEL_HPP
