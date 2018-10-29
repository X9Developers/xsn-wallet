#ifndef WALLETASSETSMODEL_HPP
#define WALLETASSETSMODEL_HPP

#include <QObject>
#include <map>
#include <vector>
#include "CoinAsset.hpp"
#include "Utils/Common.hpp"

class WalletAssetsModel : public QObject
{
    Q_OBJECT
public:
    using Assets = std::vector<CoinAsset>;
    explicit WalletAssetsModel(QString assetFilePath, QObject *parent = nullptr);
    virtual ~WalletAssetsModel();

    Assets assets() const;
    const CoinAsset &assetById(unsigned id) const;

signals:

public slots:

private:
    void init(QString assetFilePath);
    void addAsset(CoinAsset asset);

private:
    std::map<unsigned, CoinAsset> _assets;
};

#endif // WALLETASSETSMODEL_HPP
