#ifndef WALLETASSETSMODEL_HPP
#define WALLETASSETSMODEL_HPP

#include <QObject>
#include <map>
#include <vector>
#include "CoinAsset.hpp"

class WalletAssetsModel : public QObject
{
    Q_OBJECT
public:
    using Assets = std::vector<CoinAsset>;
    explicit WalletAssetsModel(QObject *parent = nullptr);
    virtual ~WalletAssetsModel();

    Assets assets() const;
    const CoinAsset &assetById(unsigned id) const;

signals:

public slots:

private:
    void init();
    void addAsset(CoinAsset asset);

private:
    std::map<unsigned, CoinAsset> _assets;
};

#endif // WALLETASSETSMODEL_HPP