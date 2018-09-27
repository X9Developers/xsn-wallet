#ifndef WALLETASSETVIEWMODEL_HPP
#define WALLETASSETVIEWMODEL_HPP

#include <QObject>
#include <memory>
#include <QPointer>

class QAbstractListModel;
class WalletTransactionsListModel;
class WalletDataSource;
class ApplicationViewModel;

class WalletAssetViewModel : public QObject
{
    Q_OBJECT

    using AssetID = int;

    Q_PROPERTY(QString balance READ balance NOTIFY balanceChanged)
    Q_PROPERTY(int currentAssetID READ currentAssetID WRITE setCurrentAssetID NOTIFY currentAssetIDChanged)
    Q_PROPERTY(QObject* transactionsListModel READ transactionsListModel NOTIFY currentAssetIDChanged)
    Q_PROPERTY(QString getReceivingAddress READ getReceivingAddress NOTIFY getReceivingAddressChanged)

public:
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
    int _currentAssetID;
    QPointer<WalletDataSource> _walletDataSource;
    using TransactionsListModelPtr = std::unique_ptr<WalletTransactionsListModel>;
    std::map<AssetID, TransactionsListModelPtr> _walletTransactionsListModels;
};

#endif // WALLETASSETVIEWMODEL_HPP
