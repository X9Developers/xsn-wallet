#include "MailHttpClientImpl.hpp"
#include <JsonUtils.h>

#include <QJsonDocument>
#include <QJsonObject>

namespace {
QString getPureEmail(const QString &email)
{
    const int beginEmailTag = email.indexOf(QChar('<'));
    if (beginEmailTag != -1) {
        const int endEmailTag = email.indexOf(QChar('>'));
        if (endEmailTag != -1) {
            return email.mid(beginEmailTag + 1, endEmailTag - beginEmailTag - 1).toLower();
        }
    }
    return email.toLower();
}

const int MAX_EMAIL_SIZE = 15 * (1 << 20);
}

MailHttpClientImpl::MailHttpClientImpl(gsl::not_null<AbstractRequestHandler*> requestHandler, QObject *parent)
    : AbstractMailHttpClient(parent)
    , _requestHandler(requestHandler)
{
}

void MailHttpClientImpl::sendCreateMailboxRequest(const QString &email, const QString &password)
{
    Q_ASSERT(!email.isEmpty());
    Q_ASSERT(!password.isEmpty());

    QJsonDocument requestBody {
        QJsonObject {
            { "email", email },
            { "password", password }
        }
    };

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit createMailboxFailed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray&, const AbstractRequestHandler::HttpHeaders&) {
        emit createMailboxFinished();
    };

    _requestHandler->makePostRequest("mailbox", requestBody, errorHandler, responseHandler);
}

void MailHttpClientImpl::sendUploadRsaRequest(const QString &email, const QString &password, const QByteArray &rsaKey)
{
    Q_ASSERT(!email.isEmpty());
    Q_ASSERT(!password.isEmpty());
    Q_ASSERT(!rsaKey.isEmpty());

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit uploadRsaFailed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray&, const AbstractRequestHandler::HttpHeaders&) {
        emit uploadRsaFinished();
    };

    // need to modify email param for RSA specifically
    QString rsaEmail = email;
    int at = email.indexOf('@');
    if (at >= 0) {
        rsaEmail = QString("%1 <%2>").arg(email.left(at - 1)).arg(email);
    }

    uploadKey("/upload_rsa", rsaEmail, password, rsaKey, errorHandler, responseHandler);
}

void MailHttpClientImpl::sendUploadEccRequest(const QString &email, const QString &password, const QByteArray &eccKey)
{
    Q_ASSERT(!email.isEmpty());
    Q_ASSERT(!password.isEmpty());
    Q_ASSERT(!eccKey.isEmpty());

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit uploadEccFailed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray&, const AbstractRequestHandler::HttpHeaders&) {
        emit uploadEccFinished();
    };

    uploadKey("upload_ecc", email, password, eccKey, errorHandler, responseHandler);
}

void MailHttpClientImpl::sendUploadEcc448Request(const QString &email, const QString &password, const QByteArray &ecc448Key)
{
    Q_ASSERT(!email.isEmpty());
    Q_ASSERT(!password.isEmpty());
    Q_ASSERT(!ecc448Key.isEmpty());

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit uploadEcc448Failed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray&, const AbstractRequestHandler::HttpHeaders&) {
        emit uploadEcc448Finished();
    };

    uploadKey("upload_ecc_448", email, password, ecc448Key, errorHandler, responseHandler);
}

void MailHttpClientImpl::sendEmailRequest(const QString &from,
                                      const QString &password,
                                      const QString &receiptId,
                                      const QStringList &recipients,
                                      const QByteArray &body)
{
    Q_ASSERT(!from.isEmpty());
    Q_ASSERT(!password.isEmpty());
    Q_ASSERT(recipients.size() > 0);
    Q_ASSERT(body.size() < MAX_EMAIL_SIZE);

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit sendEmailFailed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray&, const AbstractRequestHandler::HttpHeaders&) {
        emit sendEmailFinished();
    };

    QVariantMap parameters = QVariantMap();
    parameters["from"] = from;
    parameters["password"] = password;
    parameters["receiptId"] = receiptId;

    for (const QString& recipient : recipients) {
        parameters.insertMulti("to", getPureEmail(recipient));
    }

    _requestHandler->makePostRequest("send", parameters, body, errorHandler, responseHandler);
}

void MailHttpClientImpl::sendSearchKeysRequest(const QString &email)
{
    Q_ASSERT(!email.isEmpty());

    QVariantMap parameters;
    parameters.insert("email", email);

    auto errorHandler = [this, email](int errorCode, const QString &errorString){
        emit searchFailed(email, errorCode, errorString);
    };

    auto responseHandler = [this, email](const QByteArray &json, const AbstractRequestHandler::HttpHeaders&) {
        bool ok;
        auto response = JsonUtils::parseJsonObject(json, &ok);
        if (ok && !response.keys().isEmpty()) {
            emit searchFinished(email,
                                response.value("RSA").toString(),
                                response.value("ECC").toString(),
                                response.value("ECC_448").toString());
        } else {
            emit searchFailed(email, -1, QString("No public keys found for %1").arg(email));
        }

    };

    _requestHandler->makeGetRequest("search_all", parameters, errorHandler, responseHandler);
}

void MailHttpClientImpl::uploadKey(const QString &url,
                               const QString &email,
                               const QString &password,
                               const QByteArray &key,
                               AbstractRequestHandler::NetworkErrorHandler errorHandler,
                               AbstractRequestHandler::ResponseHandler responseHandler)
{
    QJsonDocument requestBody {
        QJsonObject {
            { "email", email },
            { "password", password },
            { "key", QJsonValue::fromVariant(key) },
        }
    };

    _requestHandler->makePostRequest(url, requestBody, errorHandler, responseHandler);
}



