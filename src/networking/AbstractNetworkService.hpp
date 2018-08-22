#ifndef ABSTRACTNETWORKSERVICE_HPP
#define ABSTRACTNETWORKSERVICE_HPP

#include <QObject>
#include "CiphrNetworkSettings.hpp

class AbstractPortalHttpClient;
class AbstractMailHttpClient;
class AbstractTextHttpClient;
class AbstractTextPushConnection;
class AbstractMailPushConnection;

class AbstractNetworkService : public QObject
{
public:
    explicit AbstractNetworkService(QObject *parent = nullptr);

public:
    virtual CiphrNetworkSettings::Environment environment() const = 0;
    virtual AbstractPortalHttpClient* portalHttpClient() const = 0;
    virtual AbstractMailHttpClient* mailHttpClient() const = 0;
    virtual AbstractTextHttpClient* textHttpClient() const = 0;
    virtual AbstractTextPushConnection* textPushClient() const = 0;
    virtual AbstractMailPushConnection* mailPushClient() const = 0;
};

#endif // ABSTRACTNETWORKSERVICE_HPP
