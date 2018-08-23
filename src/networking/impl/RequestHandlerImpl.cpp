#include "RequestHandlerImpl.hpp"

#include <QJsonDocument>
#include <QScopedPointer>
#include <QTimer>
#include <QUrlQuery>
#include <functional>

#define NetworkNotAvailableMessage  tr("Network is not available.")

RequestHandlerImpl::RequestHandlerImpl(const CiphrNetworkSettings::HttpServerSettings &settings,
                                       gsl::not_null<QNetworkAccessManager*> networkManager,
                                       QObject *parent)
    : AbstractRequestHandler(parent)
    , _settings(settings)
    , _networkAccessManager(networkManager.get())
{
}

void RequestHandlerImpl::processResponse(QNetworkReply *reply,
                                         NetworkErrorHandler errorHandler,
                                         ResponseHandler responseHandler)
{
    QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> scoped(reply);

    HttpHeaders headers;
    headers.acceptRanges = QString::fromLatin1(reply->rawHeader("Accept-Ranges"));
    headers.contentType = QString::fromLatin1(reply->rawHeader("Content-Type"));
    const auto disposition = reply->rawHeader("Content-Disposition");
    if (!disposition.isEmpty() && disposition.contains('=')) {
        int index = disposition.indexOf('=');
        headers.contentFilename = QString::fromLatin1(disposition.mid(index));
    }
    headers.contentLength = QString::fromLatin1(reply->rawHeader("Content-Length")).toInt();
    const auto contentRangeValue = QString::fromLatin1(reply->rawHeader(HttpContentRange::header()));
    if (!contentRangeValue.isEmpty()) {
        HttpContentRange::tryParse(contentRangeValue, headers.contentRange);
    }

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray response = reply->readAll();
        responseHandler(response, headers);
    }
    else
    {
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "HTTP error" << statusCode << reply->errorString();
        errorHandler(statusCode, reply->errorString());
    }
}

void RequestHandlerImpl::makeHeadRequest(const QString &path,
                                         const QVariantMap &params,
                                         RequestHandlerImpl::NetworkErrorHandler errorHandler,
                                         RequestHandlerImpl::ResponseHandler responseHandler,
                                         int retryAttempts)
{
    if (_networkAccessManager->networkAccessible() != QNetworkAccessManager::Accessible) {
        if (errorHandler) {
            errorHandler(-1, NetworkNotAvailableMessage);
        }
        return;
    }

    QNetworkRequest request(buildUrl(path, params));

    RequestMaker requestMaker = [this, request](){
        return _networkAccessManager->head(request);
    };
    QNetworkReply *networkReply = requestMaker();
    configureRetries(requestMaker, networkReply, retryAttempts);
    processNetworkReply(networkReply, errorHandler, responseHandler);
}

void RequestHandlerImpl::makeGetRequest(const QString &path,
                                        const QVariantMap &params,
                                        NetworkErrorHandler errorHandler,
                                        ResponseHandler responseHandler,
                                        const HttpRange &range,
                                        int retryAttempts)
{
    if (_networkAccessManager->networkAccessible() != QNetworkAccessManager::Accessible) {
        if (errorHandler) {
            errorHandler(-1, NetworkNotAvailableMessage);
        }
        return;
    }

    QNetworkRequest request(buildUrl(path, params));

    if (!range.isEmpty()) {
        request.setRawHeader(HttpRange::header(), range.toString().toLatin1());
    }

    RequestMaker requestMaker = [this, request](){
        return _networkAccessManager->get(request);
    };

    QNetworkReply *networkReply = requestMaker();
    configureRetries(requestMaker, networkReply, retryAttempts);
    processNetworkReply(networkReply, errorHandler, responseHandler);
}

void RequestHandlerImpl::makePostRequest(const QString &path,
                                         const QVariantMap &params,
                                         RequestHandlerImpl::NetworkErrorHandler errorHandler,
                                         RequestHandlerImpl::ResponseHandler responseHandler,
                                         int retryAttempts)
{
    if (_networkAccessManager->networkAccessible() != QNetworkAccessManager::Accessible) {
        if (errorHandler) {
            errorHandler(-1, NetworkNotAvailableMessage);
        }
        return;
    }

    QNetworkRequest request(buildUrl(path));
    QUrlQuery query;
    for (auto it = params.constBegin(); it != params.constEnd(); ++it) {
        query.addQueryItem(it.key(), it.value().toString());
    }
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    RequestMaker requestMaker = [this, request, query](){
        return _networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());
    };
    QNetworkReply *networkReply = requestMaker();

    configureRetries(requestMaker, networkReply, retryAttempts);
    processNetworkReply(networkReply, errorHandler, responseHandler);
}

void RequestHandlerImpl::makePostRequest(const QString &path,
                                         const QJsonDocument &body,
                                         NetworkErrorHandler errorHandler,
                                         ResponseHandler responseHandler,
                                         int retryAttempts)
{
    if (_networkAccessManager->networkAccessible() != QNetworkAccessManager::Accessible) {
        if (errorHandler) {
            errorHandler(-1, NetworkNotAvailableMessage);
        }
        return;
    }

    QNetworkRequest request(buildUrl(path));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    RequestMaker requestMaker = [this, request, body](){
        return _networkAccessManager->post(request, body.toJson());
    };
    QNetworkReply *networkReply = requestMaker();
    configureRetries(requestMaker, networkReply, retryAttempts);
    processNetworkReply(networkReply, errorHandler, responseHandler);
}

void RequestHandlerImpl::makePostRequest(const QString &path,
                                         const QVariantMap &params,
                                         const QByteArray &body,
                                         NetworkErrorHandler errorHandler,
                                         ResponseHandler responseHandler,
                                         const HttpContentRange &range,
                                         int retryAttempts)
{
    if (_networkAccessManager->networkAccessible() != QNetworkAccessManager::Accessible) {
        if (errorHandler) {
            errorHandler(-1, NetworkNotAvailableMessage);
        }
        return;
    }

    QNetworkRequest request(buildUrl(path, params));

    if (!range.isEmpty()) {
        request.setRawHeader(HttpContentRange::header(), range.toString().toLatin1());
    }

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
    RequestMaker requestMaker = [this, request, body](){
        return _networkAccessManager->post(request, body);
    };
    QNetworkReply *networkReply = requestMaker();
    configureRetries(requestMaker, networkReply, retryAttempts);
    processNetworkReply(networkReply, errorHandler, responseHandler);
}

void RequestHandlerImpl::checkSslCertificate(const QList<QSslError> &errors)
{
    QNetworkReply *networkReply = qobject_cast<QNetworkReply*>(sender());
    Q_ASSERT(networkReply);

    qDebug() << errors;

    if (networkReply->sslConfiguration().peerCertificate().digest(QCryptographicHash::Sha1) == _settings.sha1Digest)
        networkReply->ignoreSslErrors(errors);
    else
        networkReply->abort();
}

void RequestHandlerImpl::configureRetries(RequestMaker requestMaker,
                                          QNetworkReply *reply,
                                          int retryAttempts)
{
    if (retryAttempts > 0)
    {
        connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
                reply, [this, requestMaker, retryAttempts, previousReply = reply](QNetworkReply::NetworkError ){
            qDebug() << "Error making request:" << previousReply->errorString()
                     << "\nRetrying. Retry attempt:" << retryAttempts - 1;
            auto reply = requestMaker();
            configureRetries(requestMaker, reply, retryAttempts - 1);
        });
    }
}

void RequestHandlerImpl::processNetworkReply(QNetworkReply *reply,
                                             NetworkErrorHandler errorHandler,
                                             ResponseHandler responseHandler)
{
    QTimer::singleShot(_settings.requestTimeoutMs, reply, [reply]{
        qDebug() << "Request timeout, aborting.";
        if (!reply->isFinished()) {
            reply->abort();
        }
    });

    connect(reply, &QNetworkReply::sslErrors, this, &RequestHandlerImpl::checkSslCertificate);

    if (responseHandler) {
        auto onFinished = [reply, errorHandler, responseHandler, this](){
            processResponse(reply, errorHandler, responseHandler);
        };
        connect(reply, &QNetworkReply::finished, this, onFinished);
    }
}

QUrl RequestHandlerImpl::buildUrl(const QString &path, const QVariantMap &params)
{
    QUrl url;
    url.setScheme(_settings.scheme);
    url.setHost(_settings.host);
    url.setPort(_settings.port);

    if (path.startsWith('/')) {
        url.setPath(path);
    } else {
        url.setPath("/" + path);
    }

    QUrlQuery query;
    for (auto it = params.constBegin(); it != params.constEnd(); ++it) {
        query.addQueryItem(it.key(), QUrl::toPercentEncoding(it.value().toString()));
    }
    url.setQuery(query);

    return url;
}
