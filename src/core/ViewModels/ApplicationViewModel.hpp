#ifndef APPLICATIONVIEWMODEL_HPP
#define APPLICATIONVIEWMODEL_HPP

#include <QObject>
#include <QPointer>

class EmulatorWalletDataSource;
class WalletDataSource;

class ApplicationViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationViewModel(QObject *parent = nullptr);
    ~ApplicationViewModel();

    WalletDataSource *dataSource() const;
    static ApplicationViewModel *Instance();

private:
    void init();
    void initDataSource();

private:
    QPointer<EmulatorWalletDataSource> _emulatorWalletDataSource;
};

#endif // APPLICATIONVIEWMODEL_HPP
