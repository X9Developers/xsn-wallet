#ifndef APPLICATIONVIEWMODEL_HPP
#define APPLICATIONVIEWMODEL_HPP

#include <QObject>
#include <QPointer>
#include <memory>

class EmulatorWalletDataSource;
class WalletDataSource;
class WalletAssetsModel;

class ApplicationViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationViewModel(QObject *parent = nullptr);
    virtual ~ApplicationViewModel();

    WalletDataSource *dataSource() const;
    const WalletAssetsModel &assetsModel() const;
    static ApplicationViewModel *Instance();

private:
    void init();
    void initDataSource();
    void initWalletAssets();

private:
    QPointer<EmulatorWalletDataSource> _emulatorWalletDataSource;
    std::unique_ptr<WalletAssetsModel> _walletAssetsModel;
};

#endif // APPLICATIONVIEWMODEL_HPP
