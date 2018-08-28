#ifndef WALLETASSETVIEWMODEL_HPP
#define WALLETASSETVIEWMODEL_HPP

#include <QObject>
#include <memory>

class QAbstractListModel;
class WalletTransactionsListModel;
class WalletDataSource;
class ApplicationViewModel;

class WalletAssetViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString balance READ balance NOTIFY balanceChanged)
    Q_PROPERTY(QObject* transactionsListModel READ transactionsListModel CONSTANT)
    Q_PROPERTY(ApplicationViewModel* applicationViewModel WRITE setApplicationViewModel NOTIFY applicationViewModelChanged)

public:
    explicit WalletAssetViewModel(QObject *parent = nullptr);
    ~WalletAssetViewModel();

    QObject *transactionsListModel() const;
    QString balance() const;

    void setApplicationViewModel(ApplicationViewModel* applicationViewModel);


signals:
    void balanceChanged();
    void applicationViewModelChanged();

public slots:

private:
    void init();
    void initTransactionsListModel();

private:
    std::shared_ptr<WalletDataSource> _walletDataSource;
    std::unique_ptr<WalletTransactionsListModel> _walletTransactionsListModel;
};

#endif // WALLETASSETVIEWMODEL_HPP
