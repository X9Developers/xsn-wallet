#ifndef APPLICATIONVIEWMODEL_HPP
#define APPLICATIONVIEWMODEL_HPP

#include <QObject>
#include <QPointer>
#include <memory>

class EmulatorWalletDataSource;
class WalletDataSource;
class WalletAssetsModel;
class WalletTransactionsListModel;
class AssetsBalance;

class ApplicationViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* allTransactionsListModel READ allTransactionsListModel NOTIFY allTransactionChanged)

public:
    explicit ApplicationViewModel(QObject *parent = nullptr);
    virtual ~ApplicationViewModel();

    WalletDataSource *dataSource() const;
    const WalletAssetsModel &assetsModel() const;
    AssetsBalance *assetsBalance() const;
    static ApplicationViewModel *Instance();

    QObject *allTransactionsListModel() const;

signals:
    void allTransactionChanged();

private:
    void init();
    void initDataSource();
    void initWalletAssets();
    void initAllTransactions();
    void initWalletAssetsBalance();

private:
    QPointer<EmulatorWalletDataSource> _emulatorWalletDataSource;
    std::unique_ptr<WalletAssetsModel> _walletAssetsModel;
    std::unique_ptr<WalletTransactionsListModel> _allTransactionsListNodel;
    std::unique_ptr<AssetsBalance> _assetsBalance;
};

#endif // APPLICATIONVIEWMODEL_HPP
