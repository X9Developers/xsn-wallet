#include "TextPushConnectionImpl.hpp"
#include <codec/CiphrTextProtoCodec.hpp>
#include <codec/CiphrTextFrameLengthCodec.hpp>

#include <QTimer>

TextPushConnectionImpl::TextPushConnectionImpl(const CiphrNetworkSettings::PushServerSettings &settings, QObject *parent)
    : BasePushConnection(settings, QSharedPointer<CiphrTextFrameLengthCodec>::create(), "CT", parent)
    , _protoCodec(new CiphrTextProtoCodec(this))
{
    connect(_protoCodec, &CiphrTextProtoCodec::decodedServerHello, this, &TextPushConnectionImpl::serverHelloReceived);
    connect(_protoCodec, &CiphrTextProtoCodec::decodedPending, this, &TextPushConnectionImpl::pendingReceived);
    connect(_protoCodec, &CiphrTextProtoCodec::decodedKeepAlive, this, &TextPushConnectionImpl::keepAliveReceived);
    connect(_protoCodec, &CiphrTextProtoCodec::decodedReceived, this, &TextPushConnectionImpl::messageReceived);
    connect(_protoCodec, &CiphrTextProtoCodec::decodedReceivedNotify, this, &TextPushConnectionImpl::notifyReceived);
    connect(_protoCodec, &CiphrTextProtoCodec::decodedReceivedBroadcast, this, &TextPushConnectionImpl::broadcastReceived);
}

bool TextPushConnectionImpl::hasFullCredentials() const
{
    return _fullCredentials;
}

void TextPushConnectionImpl::open(const QString &pin, const QString &token)
{
    _fullCredentials = true;
    auto helloFrame = _protoCodec->encodeHello(token, pin, false);
    dial(helloFrame);
}

void TextPushConnectionImpl::open(const QString &token)
{
    _fullCredentials = false;
    auto helloFrame = _protoCodec->encodeTokenAuth(token);
    dial(helloFrame);
}

void TextPushConnectionImpl::broadcast(const QList<QString> &pins, const QByteArray &message)
{
    write(_protoCodec->encodeBroadcast(pins, message));
}

void TextPushConnectionImpl::send(quint64 seq, const QString &pin, const QByteArray &message, bool notify, const QString &notifyId)
{
    write(_protoCodec->encodeSend(seq, pin, message, notify, notifyId));
}

QByteArray TextPushConnectionImpl::getKeepAliveFrame()
{
    return _protoCodec->encodeKeepAlive();
}

QByteArray TextPushConnectionImpl::getLockUpdateFrame(bool locked)
{
    return _protoCodec->encodeLockUpdate(locked);
}

QByteArray TextPushConnectionImpl::getAckFrame(quint64 ack)
{
    return _protoCodec->encodeAck(ack);
}

void TextPushConnectionImpl::handleReceivedFrame(const QByteArray &frame)
{
    _protoCodec->decodeServerFrame(frame);
}

void TextPushConnectionImpl::keepAliveReceived()
{
    confirmKeepAlive();
}

void TextPushConnectionImpl::serverHelloReceived(const QString &message)
{
    qWarning() << "CT: Authentication succeeded:" << message;

    authenticate(true);

    if (_fullCredentials) {
        emit unlocked();
    } else {
        emit locked();
    }
}
