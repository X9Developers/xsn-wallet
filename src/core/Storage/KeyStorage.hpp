#ifndef KEYSTORAGE_HPP
#define KEYSTORAGE_HPP

#include <QObject>
#include <memory>
#include <Utils/ExtendedKeyPathBip44.hpp>
#include <key.h>
#include <Utils/Common.hpp>

namespace bitcoin {
class CHDChain;
};

class KeyStorage : public QObject
{
    Q_OBJECT
public:
    explicit KeyStorage(QObject *parent = nullptr);
    virtual ~KeyStorage();

    void setHDChain(const bitcoin::CHDChain &hdChain);
    const bitcoin::CHDChain &hdChain() const;

    std::pair<ExtendedKeyPathBip44, bitcoin::CExtKey> deriveNewChildKey(AssetID coinType,
                                                                        AccountIndex accountID,
                                                                        bool internal);

    bitcoin::CExtKey deriveKeyForPath(ExtendedKeyPathBip44 path);

    //    bool hasExtKeyForPath(const ExtendedKeyPathBip44 &path) const;
    //    const bitcoin::CExtKey &extKeyForPath(const ExtendedKeyPathBip44 &path) const;

signals:

public slots:

private:
    struct KeyStorageImpl;
    std::unique_ptr<KeyStorageImpl> _impl;
};

#endif // KEYSTORAGE_HPP
