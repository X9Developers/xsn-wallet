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
    Q_PROPERTY(ApplicationViewModel* applicationViewModel WRITE setApplicationViewModel CONSTANT)

public:
    EmulatorViewModel(QObject *parent = nullptr);
    ~EmulatorViewModel();

    void setApplicationViewModel(ApplicationViewModel* applicationViewModel);

public slots:
    void addTransaction();

private:
    QPointer<WalletDataSource> _walletDataSource;
};

#endif // EMULATORVIEWMODEL_HPP
