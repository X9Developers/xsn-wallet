#ifndef WALLETASSETVIEWMODEL_HPP
#define WALLETASSETVIEWMODEL_HPP

#include <QObject>
#include <memory>

class QAbstractListModel;
class WalletTransactionsListModel;

class WalletAssetViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString balance READ balance NOTIFY balanceChanged)
    Q_PROPERTY(QAbstractListModel* transactionsListModel READ transactionsListModel CONSTANT)
public:
    explicit WalletAssetViewModel(QObject *parent = nullptr);
    ~WalletAssetViewModel();

    QAbstractListModel *transactionsListModel() const;
    QString balance() const;

signals:
    void balanceChanged();

public slots:

private:
    void init();
    void initTransactionsListModel();

private:
    std::unique_ptr<WalletTransactionsListModel> _walletTransactionsListModel;
};

#endif // WALLETASSETVIEWMODEL_HPP
