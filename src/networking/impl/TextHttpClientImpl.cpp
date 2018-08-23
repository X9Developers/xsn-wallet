#include "TextHttpClientImpl.hpp"
#include <JsonUtils.h>

#include <QVariantMap>
#include <QUrl>
#include <QDebug>

TextHttpClientImpl::TextHttpClientImpl(gsl::not_null<AbstractRequestHandler*> requestHandler,
                                       QObject *parent)
    : AbstractTextHttpClient(parent)
    , _requestHandler(requestHandler)
{
}

void TextHttpClientImpl::registerRequest(const QString &deviceId,
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

    QVariantMap postData;
    postData.insert("deviceId", QUrl::toPercentEncoding(deviceId));
    postData.insert("code", QUrl::toPercentEncoding(code));
    postData.insert("publicKey", QUrl::toPercentEncoding(publicKeyBase64));
    postData.insert("publicKey448", QUrl::toPercentEncoding(publicKey448Base64));
    postData.insert("publicKeyNtru", QUrl::toPercentEncoding(publicKeyNtruBase64));
    for (auto it = preKeysBase64.cbegin(); it != preKeysBase64.cend(); ++it) {
        postData.insertMulti("preKeys", QUrl::toPercentEncoding(*it));
    }
    for (auto it = pre448KeysBase64.cbegin(); it != pre448KeysBase64.cend(); ++it) {
        postData.insertMulti("pre448Keys", QUrl::toPercentEncoding(*it));
    }
    for (auto it = preNTRUKeysBase64.cbegin(); it != preNTRUKeysBase64.cend(); ++it) {
        postData.insertMulti("preNTRUKeys", QUrl::toPercentEncoding(*it));
    }
    postData.insert("publicSigningKey448", QUrl::toPercentEncoding(publicSigningKey448Base64));
    postData.insert("signedPre448Key", QUrl::toPercentEncoding(signedPre448KeyBase64));

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit registerFailed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray& response, const AbstractRequestHandler::HttpHeaders&) {
        bool ok;
        QJsonObject json = JsonUtils::parseJsonObject(response, &ok);
        QJsonObject user = json.value("user").toObject();

        if (!ok || user.isEmpty()) {
            QString error = json.value("error").toString();
            emit registerFailed(-1, QString("Failed to register: %1").arg(error));
            return;
        }

        QString username = user.value("username").toString();
        QString pin = user.value("pin").toString();
        QString token = user.value("token").toString();

        emit registerFinished(username, pin, token);
    };

    _requestHandler->makePostRequest("register", postData, errorHandler, responseHandler);
}

void TextHttpClientImpl::setAlias(const QString &name, const QString &token)
{
    Q_ASSERT(!name.isEmpty());
    Q_ASSERT(!token.isEmpty());

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit setAliasFailed(errorCode, errorString);
    };

    auto responseHandler = [this, name](const QByteArray& response, const AbstractRequestHandler::HttpHeaders&) {
        bool ok;
        QJsonObject json = JsonUtils::parseJsonObject(response, &ok);

        if (!ok || !json.value("ok").toBool()) {
            QString error = json.value("error").toString();
            emit setAliasFailed(-1, QString("Failed to set alias: %1").arg(error));
            return;
        }

        emit setAliasFinished(name);
    };

    QVariantMap params = {
        { "name", name },
        { "token", token }
    };

    _requestHandler->makePostRequest("users/me", params, errorHandler, responseHandler);
}

void TextHttpClientImpl::lookupUsers(const QStringList &pins)
{
    Q_ASSERT(!pins.isEmpty());

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit lookupUsersFailed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray& response, const AbstractRequestHandler::HttpHeaders&) {
        bool ok;
        QJsonObject json = JsonUtils::parseJsonObject(response, &ok);
        QJsonArray jsonUsers = json.value("users").toArray();

        if (!ok || jsonUsers.isEmpty()) {
            QString error = json.value("error").toString();
            emit lookupUsersFailed(-1, QString("Failed to lookup users: %1").arg(error));
            return;
        }

        QList<User> users;
        for (const auto &jsonUser : jsonUsers) {
            User user;
            QJsonObject userObject = jsonUser.toObject();
            user.pin = userObject.value("pin").toString();
            user.name = userObject.value("name").toString();
            user.public_key = extractUserKey(userObject, "public_key");
            user.public_key_448 = extractUserKey(userObject, "public_key_448");
            user.public_signing_key_448 = extractUserKey(userObject, "public_signing_key_448");
            user.public_key_ntru = extractUserKey(userObject, "public_key_ntru");
            users << user;
        }

        emit lookupUsersFinished(users);
    };

    QVariantMap params;
    for (const QString &pin : pins) {
        params.insertMulti("pin", pin);
    }

    _requestHandler->makeGetRequest("users", params, errorHandler, responseHandler);
}

void TextHttpClientImpl::countPreKeys(const QString &pin, const QString &token)
{
    Q_ASSERT(!pin.isEmpty());
    Q_ASSERT(!token.isEmpty());

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit countPreKeysFailed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray& response, const AbstractRequestHandler::HttpHeaders&) {
        bool json_ok;
        QJsonObject json = JsonUtils::parseJsonObject(response, &json_ok);
        if (!json_ok) {
            QString error = json.value("error").toString();
            emit countPreKeysFailed(-1, QString("Failed to count prekeys: %1").arg(error));
            return;
        }

        const int count = json.value("count").toInt(0);
        emit countPreKeysFinished(count);
    };

    QVariantMap params = {
        { "pin", pin },
        { "token", token }
    };

    _requestHandler->makeGetRequest("users/me/prekeys", params, errorHandler, responseHandler);
}

void TextHttpClientImpl::fetchPreKeys(const QString &pin, const QString &token)
{
    Q_ASSERT(!pin.isEmpty());
    Q_ASSERT(!token.isEmpty());

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit fetchPreKeysFailed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray& response, const AbstractRequestHandler::HttpHeaders&) {
        bool json_ok;
        QJsonObject json = JsonUtils::parseJsonObject(response, &json_ok);
        if (!json_ok) {
            QString error = json.value("error").toString();
            emit fetchPreKeysFailed(-1, QString("Failed to fetch prekeys: %1").arg(error));
            return;
        }

        PreKeys prekeys;
        prekeys.key = extractUserKey(json, "key");
        prekeys.key448 = extractUserKey(json, "key448");
        prekeys.keyNTRU = extractUserKey(json, "keyNTRU");
        prekeys.public_key = extractUserKey(json, "public_key");
        prekeys.public_key_448 = extractUserKey(json, "public_key_448");
        prekeys.public_key_ntru = extractUserKey(json, "public_key_ntru");
        prekeys.public_signing_key_448 = extractUserKey(json, "public_signing_key_448");
        prekeys.signed_pre_448_key = extractUserKey(json, "signed_pre_448_key");

        emit fetchPreKeysFinished(prekeys);
    };

    QVariantMap params = {
        { "token", token }
    };

    const QString url = QString("users/pin/%1/prekey").arg(pin);
    _requestHandler->makePostRequest(url, params, errorHandler, responseHandler);
}

void TextHttpClientImpl::uploadPreKeys(const QString &pin,
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

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit uploadPreKeysFailed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray& response, const AbstractRequestHandler::HttpHeaders&) {
        bool json_ok;
        QJsonObject json = JsonUtils::parseJsonObject(response, &json_ok);
        if (!json_ok || !json.value("ok").toBool()) {
            QString error = json.value("error").toString();
            emit uploadPreKeysFailed(-1, QString("Failed to upload prekey: %1").arg(error));
            return;
        }

        emit uploadPreKeysFinished();
    };

    QVariantMap postData;
    postData.insert("pin", QUrl::toPercentEncoding(pin));
    postData.insert("token", QUrl::toPercentEncoding(token));
    for (auto it = preKeysBase64.cbegin(); it != preKeysBase64.cend(); ++it) {
        postData.insertMulti("preKeys", QUrl::toPercentEncoding(*it));
    }
    for (auto it = pre448KeysBase64.cbegin(); it != pre448KeysBase64.cend(); ++it) {
        postData.insertMulti("pre448Keys", QUrl::toPercentEncoding(*it));
    }
    for (auto it = preNTRUKeysBase64.cbegin(); it != preNTRUKeysBase64.cend(); ++it) {
        postData.insertMulti("preNTRUKeys", QUrl::toPercentEncoding(*it));
    }

    _requestHandler->makePostRequest("users/me/prekeys", postData, errorHandler, responseHandler);
}

void TextHttpClientImpl::rotateSignedPreKey(const QString &pin,
                                            const QString &token,
                                            const QByteArray &signedPreKeyBase64,
                                            int retry)
{
    Q_ASSERT(!pin.isEmpty());
    Q_ASSERT(!token.isEmpty());
    Q_ASSERT(!signedPreKeyBase64.isEmpty());

        auto errorHandler = [this](int errorCode, const QString &errorString){
        emit rotateSignedPreKeyFailed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray& response, const AbstractRequestHandler::HttpHeaders&) {
        bool json_ok;
        QJsonObject json = JsonUtils::parseJsonObject(response, &json_ok);
        if (!json_ok || !json.value("ok").toBool()) {
            QString error = json.value("error").toString();
            emit rotateSignedPreKeyFailed(-1, QString("Failed to rotate signed prekey: %1").arg(error));
            return;
        }

        emit rotateSignedPreKeyFinished();
    };

    QVariantMap params = {
        { "pin", pin },
        { "token", QUrl::toPercentEncoding(token) },
        { "signedPre448Key", QUrl::toPercentEncoding(signedPreKeyBase64) }
    };

    _requestHandler->makePostRequest("users/me/signedprekey",
                                     params,
                                     errorHandler,
                                     responseHandler,
                                     retry);
}

void TextHttpClientImpl::uploadBackUp(const QString &key, const QString &token, const QString &pin, const QByteArray &data)
{
    Q_ASSERT(!key.isEmpty());
    Q_ASSERT(!token.isEmpty());
    Q_ASSERT(!pin.isEmpty());
    Q_ASSERT(!data.isEmpty());

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit uploadBackUpFailed(errorCode, errorString);
    };

    auto responseHandler = [this, key](const QByteArray& response, const AbstractRequestHandler::HttpHeaders&) {
        Q_UNUSED(response);
        emit uploadBackUpFinished(key);
    };

    QVariantMap params = {
        { "token", token },
        { "pin", pin }
    };

    _requestHandler->makePostRequest("store/" + key, params, data, errorHandler, responseHandler);
}

void TextHttpClientImpl::downloadBackUp(const QString &key, const QString &token, const QString &pin)
{
    Q_ASSERT(!key.isEmpty());
    Q_ASSERT(!token.isEmpty());
    Q_ASSERT(!pin.isEmpty());

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit downloadBackUpFailed(errorCode, errorString);
    };

    auto responseHandler = [this, key](const QByteArray& response, const AbstractRequestHandler::HttpHeaders&) {
        emit downloadBackUpFinished(key, response);
    };

    QVariantMap params = {
        { "token", token },
        { "pin", pin }
    };

    _requestHandler->makeGetRequest("store/" + key, params, errorHandler, responseHandler);
}

void TextHttpClientImpl::queryAttachment(const QString &cid, const QString &name)
{
    Q_ASSERT(!cid.isEmpty());
    Q_ASSERT(!name.isEmpty());

    auto errorHandler = [=](int errorCode, const QString &errorString){
        Q_UNUSED(errorCode);
        Q_UNUSED(errorString);
        qWarning() << "queryAttachment error" << errorCode << errorString;
        emit queryAttachmentFinished(cid, name, 0);
    };

    auto responseHandler = [=](const QByteArray&, const AbstractRequestHandler::HttpHeaders &headers) {
        emit queryAttachmentFinished(cid, name, headers.contentLength);
    };

    const QString url = QString("/upload/%1/%2")
            .arg(QString(QUrl::toPercentEncoding(cid)))
            .arg(QString(QUrl::toPercentEncoding(name)));
    _requestHandler->makeHeadRequest(url, QVariantMap(), errorHandler, responseHandler);
}

void TextHttpClientImpl::downloadAttachment(const QString &cid, const QString &name, const HttpRange &range)
{
    Q_ASSERT(!cid.isEmpty());
    Q_ASSERT(!name.isEmpty());

    auto errorHandler = [=](int errorCode, const QString &errorString){
        emit downloadAttachmentFailed(cid, name, errorCode, errorString);
    };

    auto responseHandler = [=](const QByteArray& response, const AbstractRequestHandler::HttpHeaders &headers) {
        emit downloadAttachmentFinished(cid, name, response, headers.contentRange);
    };

    const QString url = QString("/upload/%1/%2")
            .arg(QString(QUrl::toPercentEncoding(cid)))
            .arg(QString(QUrl::toPercentEncoding(name)));
    _requestHandler->makeGetRequest(url, QVariantMap(), errorHandler, responseHandler, range);
}

void TextHttpClientImpl::uploadAttachment(const QString &cid,
                                          const QString &token,
                                          const QString &name,
                                          const QByteArray &data,
                                          const HttpContentRange &range)
{
    Q_ASSERT(!cid.isEmpty());
    Q_ASSERT(!token.isEmpty());
    Q_ASSERT(!name.isEmpty());
    Q_ASSERT(!data.isEmpty());

    auto errorHandler = [=](int errorCode, const QString &errorString){
        emit uploadAttachmentFailed(cid, name, errorCode, errorString);
    };

    auto responseHandler = [=](const QByteArray& response, const AbstractRequestHandler::HttpHeaders&) {
        bool json_ok;
        QJsonObject json = JsonUtils::parseJsonObject(response, &json_ok);
        if (!json_ok || !json.value("ok").toBool()) {
            QString error = json.value("error").toString();
            emit uploadAttachmentFailed(cid, name, -1, error);
        } else {
            emit uploadAttachmentFinished(cid, name);
        }
    };

    const QString url = QString("/upload/%1").arg(QString(QUrl::toPercentEncoding(cid)));

    QVariantMap params = {
        { "token",  token },
        { "name", name }
    };

    _requestHandler->makePostRequest(url, params, data, errorHandler, responseHandler, range);
}

QByteArray TextHttpClientImpl::extractUserKey(const QJsonObject &obj, const QString &field)
{
    return QByteArray::fromBase64(obj.value(field).toString().toLatin1());
}
