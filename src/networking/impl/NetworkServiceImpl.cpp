#include "NetworkServiceImpl.hpp"
#include "impl/PortalHttpClientImpl.hpp"
#include "impl/MailHttpClientImpl.hpp"
#include "impl/TextHttpClientImpl.hpp"
#include "impl/RequestHandlerImpl.hpp"
#include "impl/MailPushConnectionImpl.hpp"
#include "impl/TextPushConnectionImpl.hpp"
#include "impl/MailPushConnectionAdapter.hpp"
#include "impl/TextPushConnectionAdapter.hpp"

#include <QNetworkAccessManager>

NetworkServiceImpl::NetworkServiceImpl(CiphrNetworkSettings::Environment environment, QObject *parent)
    : QObject(parent)
    , _environment(environment)
{
    auto manager = new QNetworkAccessManager(this);

    auto portalHttpSettings = CiphrNetworkSettings::getHttpServerSettings(CiphrNetworkSettings::PortalServer, environment);
    auto portalRequestHandler = new RequestHandlerImpl(portalHttpSettings, manager, this);
    _portalHttpClient = new PortalHttpClientImpl(portalRequestHandler, this);

    auto mailHttpSettings = CiphrNetworkSettings::getHttpServerSettings(CiphrNetworkSettings::CiphrMailServer, environment);
    auto mailRequestHandler = new RequestHandlerImpl(mailHttpSettings, manager, this);
    _mailHttpClient = new MailHttpClientImpl(mailRequestHandler, this);

    auto textHttpSettings = CiphrNetworkSettings::getHttpServerSettings(CiphrNetworkSettings::CiphrTextServer, environment);
    auto textRequestHandler = new RequestHandlerImpl(textHttpSettings, manager, this);
    _textHttpClient = new TextHttpClientImpl(textRequestHandler, this);

    auto textPushSettings = CiphrNetworkSettings::getPushServerSettings(CiphrNetworkSettings::CiphrTextServer, environment);
    auto textPushClientImpl = new TextPushConnectionImpl(textPushSettings, this);
    _textPushClient = new TextPushConnectionAdapter(textPushClientImpl, this);

    auto mailPushSettings = CiphrNetworkSettings::getPushServerSettings(CiphrNetworkSettings::CiphrMailServer, environment);
    auto mailPushClientImpl = new MailPushConnectionImpl(mailPushSettings, this);
    _mailPushClient = new MailPushConnectionAdapter(mailPushClientImpl, this);
}

CiphrNetworkSettings::Environment NetworkServiceImpl::environment() const
{
    return _environment;
}

AbstractPortalHttpClient* NetworkServiceImpl::portalHttpClient() const
{
    return _portalHttpClient;
}

AbstractMailHttpClient* NetworkServiceImpl::mailHttpClient() const
{
    return _mailHttpClient;
}

AbstractTextHttpClient* NetworkServiceImpl::textHttpClient() const
{
    return _textHttpClient;
}

AbstractTextPushConnection* NetworkServiceImpl::textPushClient() const
{
    return _textPushClient;
}

AbstractMailPushConnection* NetworkServiceImpl::mailPushClient() const
{
    return _mailPushClient;
}
