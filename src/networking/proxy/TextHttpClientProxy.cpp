#include "TextHttpClientProxy.hpp"
#include <JsonUtils.h>

#include <QVariantMap>
#include <QUrl>

TextHttpClientProxy::TextHttpClientProxy(gsl::not_null<AbstractTextHttpClient*> client, QObject *parent)
    : AbstractTextHttpClient(parent)
    , _client(client)
{
    connect(_client, &AbstractTextHttpClient::registerFailed, this, &TextHttpClientProxy::registerFailed);
    connect(_client, &AbstractTextHttpClient::registerFinished, this, &TextHttpClientProxy::registerFinished);
    connect(_client, &AbstractTextHttpClient::downloadBackUpFailed, this, &TextHttpClientProxy::downloadBackUpFailed);
    connect(_client, &AbstractTextHttpClient::downloadBackUpFinished, this, &TextHttpClientProxy::downloadBackUpFinished);
    connect(_client, &AbstractTextHttpClient::uploadBackUpFailed, this, &TextHttpClientProxy::uploadBackUpFailed);
    connect(_client, &AbstractTextHttpClient::uploadBackUpFinished, this, &TextHttpClientProxy::uploadBackUpFinished);
    connect(_client, &AbstractTextHttpClient::setAliasFailed, this, &TextHttpClientProxy::setAliasFailed);
    connect(_client, &AbstractTextHttpClient::setAliasFinished, this, &TextHttpClientProxy::setAliasFinished);
    connect(_client, &AbstractTextHttpClient::lookupUsersFailed, this, &TextHttpClientProxy::lookupUsersFailed);
    connect(_client, &AbstractTextHttpClient::lookupUsersFinished, this, &TextHttpClientProxy::lookupUsersFinished);
    connect(_client, &AbstractTextHttpClient::countPreKeysFinished, this, &TextHttpClientProxy::countPreKeysFinished);
    connect(_client, &AbstractTextHttpClient::countPreKeysFailed, this, &TextHttpClientProxy::countPreKeysFailed);
    connect(_client, &AbstractTextHttpClient::fetchPreKeysFinished, this, &TextHttpClientProxy::fetchPreKeysFinished);
    connect(_client, &AbstractTextHttpClient::fetchPreKeysFailed, this, &TextHttpClientProxy::fetchPreKeysFailed);
    connect(_client, &AbstractTextHttpClient::uploadPreKeysFinished, this, &TextHttpClientProxy::uploadPreKeysFinished);
    connect(_client, &AbstractTextHttpClient::uploadPreKeysFailed, this, &TextHttpClientProxy::uploadPreKeysFailed);
    connect(_client, &AbstractTextHttpClient::rotateSignedPreKeyFinished, this, &TextHttpClientProxy::rotateSignedPreKeyFinished);
    connect(_client, &AbstractTextHttpClient::rotateSignedPreKeyFailed, this, &TextHttpClientProxy::rotateSignedPreKeyFailed);
    connect(_client, &AbstractTextHttpClient::queryAttachmentFinished, this, &TextHttpClientProxy::queryAttachmentFinished);
    connect(_client, &AbstractTextHttpClient::downloadAttachmentFinished, this, &TextHttpClientProxy::downloadAttachmentFinished);
    connect(_client, &AbstractTextHttpClient::downloadAttachmentFailed, this, &TextHttpClientProxy::downloadAttachmentFailed);
    connect(_client, &AbstractTextHttpClient::uploadAttachmentFinished, this, &TextHttpClientProxy::uploadAttachmentFinished);
    connect(_client, &AbstractTextHttpClient::uploadAttachmentFailed, this, &TextHttpClientProxy::uploadAttachmentFailed);
}

void TextHttpClientProxy::registerRequest(const QString &deviceId,
                                          const QString &code,
                                          const QString &publicKeyBase64,
                                          const QString &publicKey448Base64,
                                          const QString &publicKeyNtruBase64,
                                          const QString &publicSigningKey448Base64,
                                          const QStringList &preKeysBase64,
                                          const QStringList &pre448KeysBase64,
                                          const QStringList &preNTRUKeysBase64,
                                          const QString &signedPre448KeyBase64)
{
    Q_ASSERT(!deviceId.isEmpty());
    Q_ASSERT(!code.isEmpty());
    Q_ASSERT(!publicKeyBase64.isEmpty());
    Q_ASSERT(!publicKey448Base64.isEmpty());
    Q_ASSERT(!publicKeyNtruBase64.isEmpty());
    Q_ASSERT(!publicSigningKey448Base64.isEmpty());
    Q_ASSERT(!preKeysBase64.isEmpty());
    Q_ASSERT(!pre448KeysBase64.isEmpty());
    Q_ASSERT(!preNTRUKeysBase64.isEmpty());
    Q_ASSERT(!signedPre448KeyBase64.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->registerRequest(deviceId, code,
                                 publicKeyBase64, publicKey448Base64, publicKeyNtruBase64, publicSigningKey448Base64,
                                 preKeysBase64, pre448KeysBase64, preNTRUKeysBase64, signedPre448KeyBase64);
    },
    Qt::QueuedConnection);
}

void TextHttpClientProxy::setAlias(const QString &name, const QString &token)
{
    Q_ASSERT(!name.isEmpty());
    Q_ASSERT(!token.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->setAlias(name, token);
    },
    Qt::QueuedConnection);
}

void TextHttpClientProxy::lookupUsers(const QStringList &pins)
{
    Q_ASSERT(!pins.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->lookupUsers(pins);
    },
    Qt::QueuedConnection);
}

void TextHttpClientProxy::countPreKeys(const QString &pin, const QString &token)
{
    Q_ASSERT(!pin.isEmpty());
    Q_ASSERT(!token.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->countPreKeys(pin, token);
    },
    Qt::QueuedConnection);
}

void TextHttpClientProxy::fetchPreKeys(const QString &pin, const QString &token)
{
    Q_ASSERT(!pin.isEmpty());
    Q_ASSERT(!token.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->fetchPreKeys(pin, token);
    },
    Qt::QueuedConnection);
}

void TextHttpClientProxy::uploadPreKeys(const QString &pin,
                                        const QString &token,
                                        const QStringList &preKeysBase64,
                                        const QStringList &pre448KeysBase64,
                                        const QStringList &preNTRUKeysBase64)
{
    Q_ASSERT(!pin.isEmpty());
    Q_ASSERT(!token.isEmpty());
    Q_ASSERT(!preKeysBase64.isEmpty());
    Q_ASSERT(!pre448KeysBase64.isEmpty());
    Q_ASSERT(!preNTRUKeysBase64.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->uploadPreKeys(pin, token, preKeysBase64, pre448KeysBase64, preNTRUKeysBase64);
    },
    Qt::QueuedConnection);
}

void TextHttpClientProxy::rotateSignedPreKey(const QString &pin,
                                             const QString &token,
                                             const QByteArray &signedPreKeyBase64,
                                             int retryAttempts)
{
    Q_ASSERT(!pin.isEmpty());
    Q_ASSERT(!token.isEmpty());
    Q_ASSERT(!signedPreKeyBase64.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->rotateSignedPreKey(pin, token, signedPreKeyBase64, retryAttempts);
    },
    Qt::QueuedConnection);
}

void TextHttpClientProxy::uploadBackUp(const QString &key, const QString &token, const QString &pin, const QByteArray &data)
{
    Q_ASSERT(!key.isEmpty());
    Q_ASSERT(!token.isEmpty());
    Q_ASSERT(!pin.isEmpty());
    Q_ASSERT(!data.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->uploadBackUp(key, token, pin, data);
    },
    Qt::QueuedConnection);
}

void TextHttpClientProxy::downloadBackUp(const QString &key, const QString &token, const QString &pin)
{
    Q_ASSERT(!key.isEmpty());
    Q_ASSERT(!token.isEmpty());
    Q_ASSERT(!pin.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->downloadBackUp(key, token, pin);
    },
    Qt::QueuedConnection);
}

void TextHttpClientProxy::queryAttachment(const QString &cid, const QString &name)
{
    Q_ASSERT(!cid.isEmpty());
    Q_ASSERT(!name.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->queryAttachment(cid, name);
    },
    Qt::QueuedConnection);
}

void TextHttpClientProxy::downloadAttachment(const QString &cid, const QString &name, const HttpRange &range)
{
    Q_ASSERT(!cid.isEmpty());
    Q_ASSERT(!name.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->downloadAttachment(cid, name, range);
    },
    Qt::QueuedConnection);
}

void TextHttpClientProxy::uploadAttachment(const QString &cid, const QString &token, const QString &name, const QByteArray &data, const HttpContentRange &range)
{
    Q_ASSERT(!cid.isEmpty());
    Q_ASSERT(!token.isEmpty());
    Q_ASSERT(!name.isEmpty());
    Q_ASSERT(!data.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->uploadAttachment(cid, token, name, data, range);
    },
    Qt::QueuedConnection);
}

