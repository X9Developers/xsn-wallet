#include "CiphrNetworkSettings.hpp"
#include <QDebug>

#define DEFAULT_CONNECT_TIMEOUT_MS      30000
#define DEFAULT_HEARTBEAT_INTERVAL_MS   60000
#define DEFAULT_RECONNECT_INTERVAL_MS   10000
#define DEFAULT_MAX_FRAME_SIZE          (16 * 1024 * 1024)

CiphrNetworkSettings::PushServerSettings CiphrNetworkSettings::getPushServerSettings(
        CiphrNetworkSettings::Server server,
        CiphrNetworkSettings::Environment environment)
{
    static std::array<PushServerConfig, 4> _pushConfiguration = {
        {
            {
                CiphrNetworkSettings::CiphrMailServer,
                CiphrNetworkSettings::StagingEnvironment,
                {
                    "wbap13.protectedring.me", 5051,
                    QByteArray::fromHex("8e03b74101b07dacf9760fbc2fb166dcf1bf9ae6"),
                    DEFAULT_CONNECT_TIMEOUT_MS,
                    DEFAULT_HEARTBEAT_INTERVAL_MS,
                    DEFAULT_RECONNECT_INTERVAL_MS,
                    DEFAULT_MAX_FRAME_SIZE
                }
            },
            {
                CiphrNetworkSettings::CiphrMailServer,
                CiphrNetworkSettings::ProductionEnvironment,
                {
                    "wbap12.protectedring.me", 9393,
                    QByteArray::fromHex("d6329854b8c19838abcdf47ea1393785c9ca2f8d"),
                    DEFAULT_CONNECT_TIMEOUT_MS,
                    DEFAULT_HEARTBEAT_INTERVAL_MS,
                    DEFAULT_RECONNECT_INTERVAL_MS,
                    DEFAULT_MAX_FRAME_SIZE
                }
            },
            {
                CiphrNetworkSettings::CiphrTextServer,
                CiphrNetworkSettings::StagingEnvironment,
                {
                    "imsrv020.esim.im", 5952,
                    QByteArray::fromHex("2b77b85f213c9526a25beb31ad72e0826f8cea70"),
                    DEFAULT_CONNECT_TIMEOUT_MS,
                    DEFAULT_HEARTBEAT_INTERVAL_MS / 4, // TODO clarifying with Doug
                    DEFAULT_RECONNECT_INTERVAL_MS,
                    DEFAULT_MAX_FRAME_SIZE
                }
            },
            {
                CiphrNetworkSettings::CiphrTextServer,
                CiphrNetworkSettings::ProductionEnvironment,
                {
                    "imsrv009.esim.im", 5952,
                    QByteArray::fromHex("e850e1dc6d561194d199c3f2425c79468c229509"),
                    DEFAULT_CONNECT_TIMEOUT_MS,
                    DEFAULT_HEARTBEAT_INTERVAL_MS,
                    DEFAULT_RECONNECT_INTERVAL_MS,
                    DEFAULT_MAX_FRAME_SIZE
                }
            }
        }
    };

    for (auto config : _pushConfiguration) {
        if (config.server == server && config.environment == environment) {
            return config.settings;
        }
    }

    qCritical() << "Cannot find PUSH server config for" << server << environment;
    return PushServerSettings();
}

CiphrNetworkSettings::HttpServerSettings CiphrNetworkSettings::getHttpServerSettings(
        CiphrNetworkSettings::Server server,
        CiphrNetworkSettings::Environment environment)
{
    static std::array<HttpServerConfig, 8> _httpConfiguration {
        {
            {
                CiphrNetworkSettings::PortalServer,
                CiphrNetworkSettings::StagingEnvironment,
                {
                    "https", "cpbck1.ephemeralsupport.com", 4443,
                    QByteArray::fromHex("42f519cca4c96b8c495cc68accdb6b53a2a7c21b"),
                    DEFAULT_CONNECT_TIMEOUT_MS
                },
            },
            {
                CiphrNetworkSettings::PortalServer,
                CiphrNetworkSettings::ProductionEnvironment,
                {
                    "https", "mblreg.protectedring.me", 443,
                    QByteArray::fromHex("42f519cca4c96b8c495cc68accdb6b53a2a7c21b"),
                    DEFAULT_CONNECT_TIMEOUT_MS
                },
            },
            {
                CiphrNetworkSettings::CiphrMailServer,
                CiphrNetworkSettings::StagingEnvironment,
                {
                    "https", "wbap13.protectedring.me", 5050,
                    QByteArray::fromHex("8e03b74101b07dacf9760fbc2fb166dcf1bf9ae6"),
                    DEFAULT_CONNECT_TIMEOUT_MS
                },
            },
            {
                CiphrNetworkSettings::CiphrMailServer,
                CiphrNetworkSettings::ProductionEnvironment,
                {
                    "https", "wbap12.protectedring.me", 4547,
                    QByteArray::fromHex("d6329854b8c19838abcdf47ea1393785c9ca2f8d"),
                    DEFAULT_CONNECT_TIMEOUT_MS
                },
            },
            {
                CiphrNetworkSettings::CiphrTextServer,
                CiphrNetworkSettings::StagingEnvironment,
                {
                    "https", "imsrv020.esim.im", 5951,
                    QByteArray::fromHex("2b77b85f213c9526a25beb31ad72e0826f8cea70"),
                    DEFAULT_CONNECT_TIMEOUT_MS
                },
            },
            {
                CiphrNetworkSettings::CiphrTextServer,
                CiphrNetworkSettings::ProductionEnvironment,
                {
                    "https", "imsrv009.esim.im", 5951,
                    QByteArray::fromHex("e850e1dc6d561194d199c3f2425c79468c229509"),
                    DEFAULT_CONNECT_TIMEOUT_MS
                },
            },
            {
                CiphrNetworkSettings::CountlyServer,
                CiphrNetworkSettings::StagingEnvironment,
                {
                    "https", "ctl101.ephemeralsupport.com", 443,
                    QByteArray::fromHex("e37ac70dd11dfc073d47a962276d52708c40e091"),
                    DEFAULT_CONNECT_TIMEOUT_MS
                },
            },
            {
                CiphrNetworkSettings::CountlyServer,
                CiphrNetworkSettings::ProductionEnvironment,
                {
                    "https", "ctl101.ephemeralsupport.com", 443,
                    QByteArray::fromHex("e37ac70dd11dfc073d47a962276d52708c40e091"),
                    DEFAULT_CONNECT_TIMEOUT_MS
                },
            }
        }
    };
    for (auto && config : _httpConfiguration) {
        if (config.server == server && config.environment == environment) {
            return config.settings;
        }
    }

    qCritical() << "Cannot find HTTP server config for" << server << environment;
    return HttpServerSettings();
}
