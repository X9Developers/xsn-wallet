#include "RequestHandlerImpl.hpp"
#include <QJsonDocument>
#include <QTimer>
#include <QUrlQuery>
#include <functional>

#define NetworkNotAvailableMessage  tr("Network is not available.")

//==============================================================================

RequestHandlerImpl::RequestHandlerImpl(QNetworkAccessManager *networkManager, QObject *parent) :
    _networkAccessManager(networkManager)
{

}

//==============================================================================

RequestHandlerImpl::~RequestHandlerImpl()
{

}

//==============================================================================

void RequestHandlerImpl::makeGetRequest(const QString &path, const QVariantMap &params, RequestHandlerImpl::NetworkErrorHandler errorHandler, RequestHandlerImpl::ResponseHandler responseHandler, int retryAttempts)
{
    if (_networkAccessManager->networkAccessible() != QNetworkAccessManager::Accessible) {
        if (errorHandler) {
            errorHandler(-1, NetworkNotAvailableMessage);
        }
        return;
    }

    QNetworkRequest request(buildUrl(path, params));

    qDebug() << request.url();


    RequestMaker requestMaker = [this, request](){
        return _networkAccessManager->get(request);
    };

    processRequest(requestMaker, errorHandler, responseHandler, retryAttempts);
}

//==============================================================================

void RequestHandlerImpl::processResponse(QNetworkReply *reply, RequestHandlerImpl::NetworkErrorHandler errorHandler, RequestHandlerImpl::ResponseHandler responseHandler)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        responseHandler(response);
    } else {
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "HTTP error" << statusCode << reply->errorString();
        errorHandler(statusCode, reply->errorString());
    }
}

//==============================================================================

void RequestHandlerImpl::processRequest(RequestHandlerImpl::RequestMaker requestMaker, RequestHandlerImpl::NetworkErrorHandler errorHandler, RequestHandlerImpl::ResponseHandler responseHandler, int retryAttempts)
{
    auto reply = requestMaker();

    connect(reply, &QNetworkReply::finished, this, [=](){
        if (reply->error() == QNetworkReply::OperationCanceledError && retryAttempts > 0) {
            qWarning() << "Retrying request, attempts" << retryAttempts;
            processRequest(requestMaker, errorHandler, responseHandler, retryAttempts - 1);
        } else {
            processResponse(reply, errorHandler, responseHandler);
        }
    });
}

//==============================================================================

QUrl RequestHandlerImpl::buildUrl(const QString &path, const QVariantMap &params)
{
    QUrl url(QString("https://%1").arg(QString("xsnexplorer.io/api/%1").arg(path)));

    QUrlQuery query;
    for (auto it = params.constBegin(); it != params.constEnd(); ++it) {
        query.addQueryItem(it.key(), QUrl::toPercentEncoding(it.value().toString()));
    }
    url.setQuery(query);

    return url;
}

//==============================================================================
