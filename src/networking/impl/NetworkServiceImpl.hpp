#ifndef NETWORKSERVICEIMPL_HPP
#define NETWORKSERVICEIMPL_HPP

#include <QObject>
#include <CiphrNetworkSettings.hpp>

class AbstractPortalHttpClient;
class AbstractMailHttpClient;
class AbstractMailPushConnection;
class AbstractTextHttpClient;
class AbstractTextPushConnection;

class NetworkServiceImpl : public QObject
{
    Q_OBJECT

public:
    explicit NetworkServiceImpl(CiphrNetworkSettings::Environment environment,
                                QObject *parent = nullptr);

    CiphrNetworkSettings::Environment environment() const;
    AbstractPortalHttpClient* portalHttpClient() const;
    AbstractMailHttpClient* mailHttpClient() const;
    AbstractTextHttpClient* textHttpClient() const;
    AbstractMailPushConnection* mailPushClient() const;
    AbstractTextPushConnection* textPushClient() const;

private:
    AbstractPortalHttpClient *_portalHttpClient;
    AbstractMailHttpClient *_mailHttpClient;
    AbstractTextHttpClient *_textHttpClient;
    AbstractMailPushConnection *_mailPushClient;
    AbstractTextPushConnection *_textPushClient;
    CiphrNetworkSettings::Environment _environment;
};

#endif // NETWORKSERVICEIMPL_HPP
