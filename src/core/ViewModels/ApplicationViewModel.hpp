#ifndef APPLICATIONVIEWMODEL_HPP
#define APPLICATIONVIEWMODEL_HPP

#include <QObject>
#include <memory>

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
    std::shared_ptr<EmulatorWalletDataSource> _emulatorWalletDataSource;
};

#endif // APPLICATIONVIEWMODEL_HPP
