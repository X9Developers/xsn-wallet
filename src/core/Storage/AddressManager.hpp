#ifndef ADDRESSMANAGER_HPP
#define ADDRESSMANAGER_HPP

#include <QObject>
#include <memory>
#include <Utils/Common.hpp>

class AddressManager : public QObject
{
    Q_OBJECT
public:
    using Addresses = std::vector<QString>;
    explicit AddressManager(QObject *parent = nullptr);
    virtual ~AddressManager();

    QString externalAddress() const;
    QString changeAddress() const;

    Addresses addresses(AssetID assetID) const;

    void markAddressAsUsed(QString address);

signals:

public slots:

private:
    struct AddressManagerImpl;
    std::unique_ptr<AddressManagerImpl> _impl;

};

#endif // ADDRESSMANAGER_HPP
