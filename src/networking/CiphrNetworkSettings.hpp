#ifndef CIPHRNETWORKSETTINGS_HPP
#define CIPHRNETWORKSETTINGS_HPP

#include <QString>
#include <QByteArray>
#include <array>

/*
 * https://portal.mblsft.com:8090/display/DT/Servers
 */
class CiphrNetworkSettings
{
public:
    enum Environment {
        StagingEnvironment,
        ProductionEnvironment
    };

    enum Server {
        PortalServer,
        CiphrMailServer,
        CiphrTextServer,
        CountlyServer
    };

    struct PushServerSettings {
        QString host;
        quint16 port;
        QByteArray sha1Digest;
        int connectTimeoutMs;
        int heartbeatIntervalMs;
        int reconnectIntervalMs;
        int maxFrameSize;
    };

    struct HttpServerSettings {
        QString scheme;
        QString host;
        quint16 port;
        QByteArray sha1Digest;
        int requestTimeoutMs;
    };

    static PushServerSettings getPushServerSettings(Server server, Environment environment);
    static HttpServerSettings getHttpServerSettings(Server server, Environment environment);

private:
    struct PushServerConfig {
        Server server;
        Environment environment;
        PushServerSettings settings;
    };

    struct HttpServerConfig {
        Server server;
        Environment environment;
        HttpServerSettings settings;
    };

    CiphrNetworkSettings() = default;

};

#endif // CIPHRNETWORKSETTINGS_HPP
