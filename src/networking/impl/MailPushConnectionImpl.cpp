#include "MailPushConnectionImpl.hpp"
#include <codec/CiphrMailProtoCodec.hpp>
#include <codec/CiphrMailFrameLengthCodec.hpp>
#include <impl/BasePushConnection.hpp>

#include <QTimer>

MailPushConnectionImpl::MailPushConnectionImpl(
        const CiphrNetworkSettings::PushServerSettings &settings,
        QObject *parent)
    : BasePushConnection(settings, QSharedPointer<CiphrMailFrameLengthCodec>::create(), "CM", parent)
    , _protoCodec(new CiphrMailProtoCodec(this))
{
    connect(_protoCodec, &CiphrMailProtoCodec::decodedServerHello, this, &MailPushConnectionImpl::serverHelloReceived);
    connect(_protoCodec, &CiphrMailProtoCodec::decodedEmail, this, &MailPushConnectionImpl::mailReceived);
    connect(_protoCodec, &CiphrMailProtoCodec::decodedPending, this, &MailPushConnectionImpl::pendingReceived);
    connect(_protoCodec, &CiphrMailProtoCodec::decodedDeliveryReceipt, this, &MailPushConnectionImpl::deliveryReceiptReceived);
    connect(_protoCodec, &CiphrMailProtoCodec::decodedReadReceipt, this, &MailPushConnectionImpl::readReceiptReceived);
    connect(_protoCodec, &CiphrMailProtoCodec::decodedKeepAlive, this, &MailPushConnectionImpl::keepAliveReceived);
}

bool MailPushConnectionImpl::hasFullCredentials() const
{
    return _fullCredentials;
}

void MailPushConnectionImpl::open(const QString &email, const QString &password, const CiphrMailProtoCodec::ClientInfo &clientInfo)
{
    _fullCredentials = true;
    auto helloFrame = _protoCodec->encodeClientHello(email, password, clientInfo);
    dial(helloFrame);
}

void MailPushConnectionImpl::open(const QString &token, const CiphrMailProtoCodec::ClientInfo &clientInfo)
{
    _fullCredentials = false;
    auto helloFrame = _protoCodec->encodeTokenAuth(token, clientInfo);
    dial(helloFrame);
}

QByteArray MailPushConnectionImpl::getKeepAliveFrame()
{
    return _protoCodec->encodeKeepAlive();
}

QByteArray MailPushConnectionImpl::getLockUpdateFrame(bool locked)
{
    return _protoCodec->encodeReady(locked);
}

QByteArray MailPushConnectionImpl::getAckFrame(quint64 ack)
{
    return _protoCodec->encodeAck(ack);
}

void MailPushConnectionImpl::handleReceivedFrame(const QByteArray &frame)
{
    _protoCodec->decodeServerFrame(frame);
}

void MailPushConnectionImpl::keepAliveReceived()
{
    confirmKeepAlive();
}

void MailPushConnectionImpl::serverHelloReceived(bool authenticated, const QString &message)
{
    if (!authenticated) {
        qWarning() << "CM: Authentication failed:" << message;
    } else {
        qWarning() << "CM: Authentication succeeded.";
    }

    authenticate(authenticated);

    if (_fullCredentials) {
        unlock();
    } else {
        lock();
    }
}
