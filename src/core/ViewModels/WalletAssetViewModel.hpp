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

    using AssetID = QString;

    Q_PROPERTY(QString balance READ balance NOTIFY balanceChanged)
    Q_PROPERTY(QString currentAssetID READ currentAssetID WRITE setCurrentAssetID NOTIFY currentAssetIDChanged)
    Q_PROPERTY(QObject* transactionsListModel READ transactionsListModel NOTIFY currentAssetIDChanged)
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

public slots:
    void initialize(ApplicationViewModel* applicationViewModel);
    QString getReceivingAddress() const;

private:
    void init();

private:
    QString _currentAssetID;
    QPointer<WalletDataSource> _walletDataSource;
    using TransactionsListModelPtr = std::unique_ptr<WalletTransactionsListModel>;
    std::map<AssetID, TransactionsListModelPtr> _walletTransactionsListModels;
};

#endif // WALLETASSETVIEWMODEL_HPP
