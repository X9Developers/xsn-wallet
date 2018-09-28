#ifndef WALLETASSETVIEWMODEL_HPP
#define WALLETASSETVIEWMODEL_HPP

#include <QObject>
#include <memory>
#include <QPointer>

class QAbstractListModel;
class WalletTransactionsListModel;
class WalletDataSource;
class WalletAssetsModel;
class ApplicationViewModel;

class WalletAssetViewModel : public QObject
{
    Q_OBJECT

//<<<<<<< HEAD
//    using AssetID = int;

    Q_PROPERTY(QString balance READ balance NOTIFY balanceChanged)
    Q_PROPERTY(int currentAssetID READ currentAssetID WRITE setCurrentAssetID NOTIFY currentAssetIDChanged)
    Q_PROPERTY(QObject* transactionsListModel READ transactionsListModel NOTIFY currentAssetIDChanged)
    Q_PROPERTY(QString getReceivingAddress READ getReceivingAddress NOTIFY getReceivingAddressChanged)
//=======
//    Q_PROPERTY(QString balance READ balance NOTIFY balanceChanged)
//    Q_PROPERTY(unsigned currentAssetID READ currentAssetID WRITE setCurrentAssetID NOTIFY currentAssetIDChanged)
//    Q_PROPERTY(QObject* transactionsListModel READ transactionsListModel NOTIFY currentAssetIDChanged)
//>>>>>>> 342e1fc1dbb6cdf9e07b7bf5a0681795c635bc30

public:
    using AssetID = unsigned;
    explicit WalletAssetViewModel(QObject *parent = nullptr);
    ~WalletAssetViewModel();

    QObject *transactionsListModel();
    QString balance() const;
    AssetID currentAssetID() const;

    void setCurrentAssetID(AssetID assetID);

signals:
    void balanceChanged();
    void currentAssetIDChanged();
    void transactionsListModelChanged();
    void getReceivingAddressChanged();

public slots:
    void initialize(ApplicationViewModel* applicationViewModel);
    QString getReceivingAddress() const;

private:
    void init();

private:
//<<<<<<< HEAD
//    int _currentAssetID;
//=======
    AssetID _currentAssetID;
//>>>>>>> 342e1fc1dbb6cdf9e07b7bf5a0681795c635bc30
    QPointer<WalletDataSource> _walletDataSource;
    QPointer<const WalletAssetsModel> _walletAssetsModel;
    using TransactionsListModelPtr = std::unique_ptr<WalletTransactionsListModel>;
    std::map<AssetID, TransactionsListModelPtr> _walletTransactionsListModels;
};

Q_DECLARE_METATYPE(WalletAssetViewModel::AssetID)

#endif // WALLETASSETVIEWMODEL_HPP
