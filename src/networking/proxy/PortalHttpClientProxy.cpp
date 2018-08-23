#include "PortalHttpClientProxy.hpp"

PortalHttpClientProxy::PortalHttpClientProxy(gsl::not_null<AbstractPortalHttpClient*> client, QObject *parent)
    : AbstractPortalHttpClient(parent)
    , _client(client)
{
    connect(_client, &AbstractPortalHttpClient::activateCompletedFailed, this, &PortalHttpClientProxy::activateCompletedFailed);
    connect(_client, &AbstractPortalHttpClient::activateCompletedFinished, this, &PortalHttpClientProxy::activateCompletedFinished);
    connect(_client, &AbstractPortalHttpClient::activateFailed, this, &PortalHttpClientProxy::activateFailed);
    connect(_client, &AbstractPortalHttpClient::activateFinished, this, &PortalHttpClientProxy::activateFinished);
    connect(_client, &AbstractPortalHttpClient::getMyAccountFailed, this, &PortalHttpClientProxy::getMyAccountFailed);
    connect(_client, &AbstractPortalHttpClient::getMyAccountFinished, this, &PortalHttpClientProxy::getMyAccountFinished);
}

void PortalHttpClientProxy::sendActivateRequest(const QString &imei, const QString &code)
{
    Q_ASSERT(!imei.isEmpty());
    Q_ASSERT(!code.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->sendActivateRequest(imei, code);
    },
    Qt::QueuedConnection);
}

void PortalHttpClientProxy::sendActivateCompletedRequest(const QString &token)
{
    Q_ASSERT(!token.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->sendActivateCompletedRequest(token);
    },
    Qt::QueuedConnection);
}

void PortalHttpClientProxy::sendGetMyAccountRequest(const QString &token)
{
    Q_ASSERT(!token.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
        _client->sendGetMyAccountRequest(token);
    },
    Qt::QueuedConnection);
}
