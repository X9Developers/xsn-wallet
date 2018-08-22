#ifndef TEXTHTTPCLIENTPROXY_HPP
#define TEXTHTTPCLIENTPROXY_HPP

#include <QObject>
#include <QStringList>
#include <AbstractTextHttpClient.hpp>

#include <gsl/gsl>

class TextHttpClientProxy : public AbstractTextHttpClient
{
    Q_OBJECT

public:
    TextHttpClientProxy(gsl::not_null<AbstractTextHttpClient*> client, QObject *parent = nullptr);

    void registerRequest(const QString &deviceId,
                         const QString &code,
                         const QString &publicKeyBase64,
                         const QString &publicKey448Base64,
                         const QString &publicKeyNtruBase64,
                         const QString &publicSigningKey448Base64,
                         const QStringList &preKeysBase64,
                         const QStringList &pre448KeysBase64,
                         const QStringList &preNTRUKeysBase64,
                         const QString &signedPre448KeyBase64) override;

    void setAlias(const QString &name, const QString &token) override;

    void lookupUsers(const QStringList &pins) override;

    void countPreKeys(const QString &pin, const QString &token) override;

    void fetchPreKeys(const QString &pin, const QString &token) override;

    void uploadPreKeys(const QString &pin,
                       const QString &token,
                       const QStringList &preKeysBase64,
                       const QStringList &pre448KeysBase64,
                       const QStringList &preNTRUKeysBase64) override;

    void rotateSignedPreKey(const QString &pin,
                            const QString &token,
                            const QByteArray &signedPreKeyBase64,
                            int retryAttempts = 0) override;

    void uploadBackUp(const QString &key,
                      const QString &token,
                      const QString &pin,
                      const QByteArray &data) override;

    void downloadBackUp(const QString &key,
                        const QString &token,
                        const QString &pin) override;

    void queryAttachment(const QString &cid,
                         const QString &name) override;

    void downloadAttachment(const QString &cid,
                            const QString &name,
                            const HttpRange &range) override;

    void uploadAttachment(const QString &cid,
                          const QString &token,
                          const QString &name,
                          const QByteArray &data,
                          const HttpContentRange &range) override;

private:
    AbstractTextHttpClient *_client;
};

#endif // TEXTHTTPCLIENTPROXY_HPP
