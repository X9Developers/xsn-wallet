#include "CiphrTextProtoCodec.hpp"

#include "protobuf/Transport.pb.h"

using namespace main;

CiphrTextProtoCodec::CiphrTextProtoCodec(QObject *parent)
    : QObject(parent)
{
}

QByteArray CiphrTextProtoCodec::encodeHello(const QString &token, const QString &pin, bool locked)
{
    Hello hello;
    PushFrame frame;

    hello.set_token(token.toStdString());
    hello.set_pin(pin.toStdString());
    hello.set_locked(locked);
    frame.set_allocated_hello(&hello);

    QByteArray blob(frame.ByteSize(), Qt::Uninitialized);
    frame.SerializeToArray(blob.data(), blob.size());

    frame.release_hello();

    return blob;
}

QByteArray CiphrTextProtoCodec::encodeTokenAuth(const QString &token)
{
    TokenAuth tokenAuth;
    PushFrame frame;

    tokenAuth.set_token(token.toStdString());
    frame.set_allocated_tokenauth(&tokenAuth);

    QByteArray blob(frame.ByteSize(), Qt::Uninitialized);
    frame.SerializeToArray(blob.data(), blob.size());

    frame.release_tokenauth();

    return blob;
}

QByteArray CiphrTextProtoCodec::encodeAck(quint64 ack)
{
    Ack ackMessage;
    PushFrame frame;

    ackMessage.set_ack(ack);
    frame.set_allocated_ack(&ackMessage);

    QByteArray blob(frame.ByteSize(), Qt::Uninitialized);
    frame.SerializeToArray(blob.data(), blob.size());

    frame.release_ack();

    return blob;
}

QByteArray CiphrTextProtoCodec::encodeKeepAlive()
{
    KeepAlive keepAlive;
    PushFrame frame;

    frame.set_allocated_keepalive(&keepAlive);

    QByteArray blob(frame.ByteSize(), Qt::Uninitialized);
    frame.SerializeToArray(blob.data(), blob.size());

    frame.release_keepalive();

    return blob;
}

QByteArray CiphrTextProtoCodec::encodeLockUpdate(bool locked)
{
    LockUpdate lockUpdate;
    PushFrame frame;

    lockUpdate.set_locked(locked);
    frame.set_allocated_lockupdate(&lockUpdate);

    QByteArray blob(frame.ByteSize(), Qt::Uninitialized);
    frame.SerializeToArray(blob.data(), blob.size());

    frame.release_lockupdate();

    return blob;
}

QByteArray CiphrTextProtoCodec::encodeBroadcast(const QList<QString> &pins, const QByteArray &message)
{
    SendBroadcast broadcast;

    for (const QString& pin : pins) {
        broadcast.add_pins(pin.toStdString());
    }

    broadcast.set_message(message.toStdString());

    PushFrame frame;
    frame.set_allocated_broadcast(&broadcast);

    QByteArray blob(frame.ByteSize(), Qt::Uninitialized);
    frame.SerializeToArray(blob.data(), blob.size());

    frame.release_broadcast();

    return blob;
}

QByteArray CiphrTextProtoCodec::encodeSend(quint64 seq, const QString &pin, const QByteArray &message, bool notify, const QString &notifyId)
{
    Send send;
    PushFrame frame;

    send.set_pin(pin.toStdString());
    send.set_message(message.toStdString());
    send.set_notify(notify);
    if (notify) {
        send.set_notifyid(notifyId.toStdString());
    }

    frame.set_allocated_send(&send);
    frame.set_seq(seq);

    QByteArray blob(frame.ByteSize(), Qt::Uninitialized);
    frame.SerializeToArray(blob.data(), blob.size());

    frame.release_send();

    return blob;
}

void CiphrTextProtoCodec::decodeServerFrame(const QByteArray &blob)
{
    ServerFrame frame;
    frame.ParseFromArray(blob.constData(), blob.length());

    if (frame.has_hello()) {
        emit decodedServerHello(QString::fromStdString(frame.hello().message()));
    }

    if (frame.has_ack()) {
        emit decodedServerAck(frame.ack().ack());
    }

    if (frame.has_keepalive()) {
        emit decodedKeepAlive();
    }

    if (frame.has_pending()) {
        emit decodedPending(frame.pending().notifications());
    }

    if (frame.has_rcvdbroadcast()) {
        auto pin = QString::fromStdString(frame.rcvdbroadcast().pin());
        auto message = QByteArray::fromStdString(frame.rcvdbroadcast().message());
        emit decodedReceivedBroadcast(pin, message);
    }

    if (frame.has_rcvd()) {
        auto pin = QString::fromStdString(frame.rcvd().pin());
        auto message = QByteArray::fromStdString(frame.rcvd().message());
        auto receiptId = QString();
        if (frame.rcvd().has_notifyrcpt()) {
            receiptId = QString::fromStdString(frame.rcvd().notifyrcpt().receiptid());
            emit decodedReceivedNotify(frame.seq(), pin, receiptId);
        } else {
            emit decodedReceived(frame.seq(), pin, message);
        }
    }
}
