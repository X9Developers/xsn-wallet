#include "NetworkService.hpp"
#include "proxy/PortalHttpClientProxy.hpp"
#include "proxy/TextHttpClientProxy.hpp"
#include "proxy/MailHttpClientProxy.hpp"
#include "proxy/MailPushConnectionProxy.hpp"
#include "proxy/TextPushConnectionProxy.hpp"

#include <QNetworkAccessManager>

NetworkService::NetworkService(CiphrNetworkSettings::Environment environment, QObject *parent)
    : AbstractNetworkService(parent)
    , _thread(new NetworkServiceImpl(environment), "network-service-thread", this)
{
    _portalHttpClient = new PortalHttpClientProxy(_thread.worker()->portalHttpClient(), this);
    _mailHttpClient = new MailHttpClientProxy(_thread.worker()->mailHttpClient(), this);
    _textHttpClient = new TextHttpClientProxy(_thread.worker()->textHttpClient(), this);
    _mailPushClient = new MailPushConnectionProxy(_thread.worker()->mailPushClient(), this);
    _textPushClient = new TextPushConnectionProxy(_thread.worker()->textPushClient(), this);
}

CiphrNetworkSettings::Environment NetworkService::environment() const
{
    return _thread.worker()->environment();
}

AbstractPortalHttpClient* NetworkService::portalHttpClient() const
{
    return _portalHttpClient;
}

AbstractMailHttpClient* NetworkService::mailHttpClient() const
{
    return _mailHttpClient;
}

AbstractTextHttpClient* NetworkService::textHttpClient() const
{
    return _textHttpClient;
}

AbstractTextPushConnection* NetworkService::textPushClient() const
{
    return _textPushClient;
}

AbstractMailPushConnection* NetworkService::mailPushClient() const
{
    return _mailPushClient;
}
