#ifndef MAILPUSHCONNECTIONIMPL_HPP
#define MAILPUSHCONNECTIONIMPL_HPP

#include <QObject>
#include <AbstractMailPushConnection.hpp>
#include <CiphrNetworkSettings.hpp>
#include <impl/BasePushConnection.hpp>
#include <codec/CiphrMailProtoCodec.hpp>

class MailPushConnectionImpl : public BasePushConnection
{
    Q_OBJECT

public:
    MailPushConnectionImpl(const CiphrNetworkSettings::PushServerSettings &settings,
                           QObject *parent = nullptr);

    bool hasFullCredentials() const;

public slots:
    void open(const QString& email, const QString& password, const CiphrMailProtoCodec::ClientInfo &clientInfo);
    void open(const QString& token, const CiphrMailProtoCodec::ClientInfo &clientInfo);

signals:
    void pendingReceived(quint64 pending);
    void mailReceived(quint64 seq, const QString &uid, quint64 displayTime, const QByteArray &body);
    void deliveryReceiptReceived(quint64 seq, const QString &id);
    void readReceiptReceived(quint64 seq, const QString &id);

protected:
    QByteArray getKeepAliveFrame() override;
    QByteArray getLockUpdateFrame(bool locked) override;
    QByteArray getAckFrame(quint64 ack) override;
    void handleReceivedFrame(const QByteArray &frame) override;

private slots:
    void keepAliveReceived();
    void serverHelloReceived(bool authenticated, const QString &message);

private:
    CiphrMailProtoCodec *_protoCodec;
    bool _fullCredentials;
};

#endif // MAILPUSHCONNECTIONIMPL_HPP
