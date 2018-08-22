#ifndef ABSTRACTTESTHTTPCLIENT_HPP
#define ABSTRACTTESTHTTPCLIENT_HPP

#include <QObject>
#include <QList>
#include <QByteArray>
#include <HttpRange.hpp>
#include <HttpContentRange.hpp>

class AbstractTextHttpClient : public QObject
{
    Q_OBJECT

public:
    explicit AbstractTextHttpClient(QObject *parent = nullptr);

    struct User {
        QString pin;
        QString name;
        QByteArray public_key;
        QByteArray public_key_448;
        QByteArray public_signing_key_448;
        QByteArray public_key_ntru;
    };

    struct PreKeys {
        QByteArray key;
        QByteArray key448;
        QByteArray keyNTRU;
        QByteArray public_key;
        QByteArray public_key_448;
        QByteArray public_signing_key_448;
        QByteArray signed_pre_448_key;
        QByteArray public_key_ntru;
    };

public:
    virtual void registerRequest(const QString &deviceId,
                                 const QString &code,
                                 const QString &publicKeyBase64,
                                 const QString &publicKey448Base64,
                                 const QString &publicKeyNtruBase64,
                                 const QString &publicSigningKey448Base64,
                                 const QStringList &preKeysBase64,
                                 const QStringList &pre448KeysBase64,
                                 const QStringList &preNTRUKeysBase64,
                                 const QString &signedPre448KeyBase64) = 0;

    virtual void setAlias(const QString& name, const QString& token) = 0;

    virtual void lookupUsers(const QStringList &pins) = 0;

    virtual void countPreKeys(const QString &pin,
                              const QString &token) = 0;

    virtual void fetchPreKeys(const QString &pin,
                              const QString &token) = 0;

    virtual void uploadPreKeys(const QString &pin,
                               const QString &token,
                               const QStringList &preKeysBase64,
                               const QStringList &pre448KeysBase64,
                               const QStringList &preNTRUKeysBase64) = 0;

    virtual void rotateSignedPreKey(const QString &pin,
                                    const QString &token,
                                    const QByteArray &signedPreKeyBase64,
                                    int retry = 0) = 0;

    virtual void uploadBackUp(const QString& key,
                              const QString& token,
                              const QString& pin,
                              const QByteArray& data) = 0;

    virtual void downloadBackUp(const QString& key,
                                const QString& token,
                                const QString& pin) = 0;

    virtual void queryAttachment(const QString &cid,
                                 const QString &name) = 0;

    virtual void downloadAttachment(const QString &cid,
                                    const QString &name,
                                    const HttpRange &range) = 0;

    virtual void uploadAttachment(const QString &cid,
                                  const QString &token,
                                  const QString &name,
                                  const QByteArray &data,
                                  const HttpContentRange &range) = 0;

public:
    static const int RETRIES_COUNT = 3;

signals:
    void registerFinished(const QString &username,
                          const QString &pin,
                          const QString &token);
    void registerFailed(int error, const QString &message);

    void setAliasFinished(const QString &name);
    void setAliasFailed(int error, const QString &message);

    void lookupUsersFinished(const QList<User> users);
    void lookupUsersFailed(int error, const QString &message);

    void countPreKeysFinished(int count);
    void countPreKeysFailed(int error, const QString &message);

    void fetchPreKeysFinished(const PreKeys prekeys);
    void fetchPreKeysFailed(int error, const QString &message);

    void uploadPreKeysFinished();
    void uploadPreKeysFailed(int error, const QString &message);

    void rotateSignedPreKeyFinished();
    void rotateSignedPreKeyFailed(int error, const QString &message);

    void uploadBackUpFailed(int error, const QString &message);
    void uploadBackUpFinished(const QString& key);

    void downloadBackUpFailed(int error, const QString &message);
    void downloadBackUpFinished(const QString& key, const QByteArray &data);

    void downloadAttachmentFinished(const QString &cid, const QString &name, const QByteArray &data, const HttpContentRange &range);
    void downloadAttachmentFailed(const QString &cid, const QString &name, int error, const QString &message);

    void uploadAttachmentFinished(const QString &cid, const QString &name);
    void uploadAttachmentFailed(const QString &cid, const QString &name, int error, const QString &message);

    void queryAttachmentFinished(const QString &cid, const QString &name, qint64 filesize);
};

Q_DECLARE_METATYPE(HttpRange)
Q_DECLARE_METATYPE(HttpContentRange)
Q_DECLARE_METATYPE(AbstractTextHttpClient::User)
Q_DECLARE_METATYPE(AbstractTextHttpClient::PreKeys)

#endif // ABSTRACTTESTHTTPCLIENT_HPP
