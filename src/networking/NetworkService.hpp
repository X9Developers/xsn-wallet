#ifndef NETWORKSERVICE_HPP
#define NETWORKSERVICE_HPP

#include <QObject>
#include <QThread>
#include <AbstractNetworkService.hpp>
#include <Thread.hpp>
#include <impl/NetworkServiceImpl.hpp>

class AbstractPortalHttpClient;
class AbstractMailHttpClient;
class AbstractMailPushConnection;
class AbstractTextHttpClient;
class AbstractTextPushConnection;

// Provides thread-safe http and push clients
class NetworkService : public AbstractNetworkService
{
public:
    explicit NetworkService(CiphrNetworkSettings::Environment environment,
                            QObject *parent = nullptr);

public:
    CiphrNetworkSettings::Environment environment() const;
    AbstractPortalHttpClient* portalHttpClient() const;
    AbstractMailHttpClient* mailHttpClient() const;
    AbstractMailPushConnection* mailPushClient() const;
    AbstractTextHttpClient* textHttpClient() const;
    AbstractTextPushConnection* textPushClient() const;

private:
    Q_DISABLE_COPY(NetworkService)

private:
    Thread<NetworkServiceImpl> _thread;
    AbstractPortalHttpClient *_portalHttpClient;
    AbstractMailHttpClient *_mailHttpClient;
    AbstractMailPushConnection *_mailPushClient;
    AbstractTextHttpClient *_textHttpClient;
    AbstractTextPushConnection *_textPushClient;
};

#endif // NETWORKSERVICE_HPP
