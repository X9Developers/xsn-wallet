#ifndef CIPHRMAILPROTOCODEC_HPP
#define CIPHRMAILPROTOCODEC_HPP

#include <QObject>
#include <QByteArray>
#include <QString>

class CiphrMailProtoCodec : public QObject
{
    Q_OBJECT

public:
    static const int LatestProtocol = 2;

    struct ClientInfo {
        // an IMEI uniquely identifies the device
        QString imei;
        // String describing the model of device, e.g. "XT1095"
        QString deviceModel;
        // Device OS. Should be one of 'Android' or 'BlackBerry'
        QString deviceOs;
        // OS-specific version number, e.g. "5.0"
        QString deviceOsVersion;
        // Ciphr Mail app version
        QString cmVersion;
        // Ciphr Text app version
        QString ctVersion;
        // Vault app version
        QString vaultVersion;
    };

    explicit CiphrMailProtoCodec(QObject* parent = nullptr);

    QByteArray encodeClientHello(
            const QString &email,
            const QString &password,
            const ClientInfo &clientInfo,
            int protocol = LatestProtocol);
    QByteArray encodeTokenAuth(
            const QString &token,
            const ClientInfo &clientInfo,
            int protocol = LatestProtocol);
    QByteArray encodeKeepAlive();
    QByteArray encodeReady(bool locked);
    QByteArray encodeAck(quint64 seq);

    void decodeServerFrame(const QByteArray &blob);

signals:
    void decodedPending(quint64 emails);
    void decodedKeepAlive();
    void decodedServerHello(bool authenticated, const QString &message);
    void decodedEmail(quint64 seq, const QString &uid, quint64 displayTime, const QByteArray &body);
    void decodedDeliveryReceipt(quint64 seq, const QString &id);
    void decodedReadReceipt(quint64 seq, const QString &id);
};

#endif // CIPHRMAILPROTOCODEC_HPP
