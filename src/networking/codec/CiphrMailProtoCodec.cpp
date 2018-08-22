#include "CiphrMailProtoCodec.hpp"

#include "protobuf/PushApiV2.pb.h"

using namespace pushv2;

static void copyClientInfo(const CiphrMailProtoCodec::ClientInfo &from, pushv2::ClientInfo& to) {
    to.set_imei(from.imei.toStdString());
    to.set_device_model(from.deviceModel.toStdString());
    to.set_device_os(from.deviceOs.toStdString());
    to.set_device_os_version(from.deviceOsVersion.toStdString());
    to.set_cm_version(from.cmVersion.toStdString());
    to.set_ct_version(from.ctVersion.toStdString());
    to.set_vault_version(from.vaultVersion.toStdString());
}

CiphrMailProtoCodec::CiphrMailProtoCodec(QObject *parent)
    : QObject(parent)
{
}

QByteArray CiphrMailProtoCodec::encodeClientHello(
        const QString &email,
        const QString &password,
        const CiphrMailProtoCodec::ClientInfo &clientInfo,
        int protocol)
{
    pushv2::ClientInfo info;
    copyClientInfo(clientInfo, info);

    ClientHello clientHello;
    clientHello.set_email(email.toStdString());
    clientHello.set_password(password.toStdString());
    clientHello.set_protocol(protocol);
    clientHello.set_allocated_client_info(&info);

    ClientFrame frame;
    frame.set_allocated_hello(&clientHello);

    QByteArray blob(frame.ByteSize(), Qt::Uninitialized);
    frame.SerializeToArray(blob.data(), blob.size());

    clientHello.release_client_info();
    frame.release_hello();

    return blob;
}

QByteArray CiphrMailProtoCodec::encodeTokenAuth(
        const QString &token,
        const CiphrMailProtoCodec::ClientInfo &clientInfo,
        int protocol)
{
    pushv2::ClientInfo info;
    copyClientInfo(clientInfo, info);

    TokenAuth tokenAuth;
    tokenAuth.set_token(token.toStdString());
    tokenAuth.set_protocol(protocol);
    tokenAuth.set_allocated_client_info(&info);

    ClientFrame frame;
    frame.set_allocated_tokenauth(&tokenAuth);

    QByteArray blob(frame.ByteSize(), Qt::Uninitialized);
    frame.SerializeToArray(blob.data(), blob.size());

    tokenAuth.release_client_info();
    frame.release_tokenauth();

    return blob;
}

QByteArray CiphrMailProtoCodec::encodeKeepAlive()
{
    KeepAlive keepAlive;
    ClientFrame frame;

    frame.set_allocated_keepalive(&keepAlive);

    QByteArray blob(frame.ByteSize(), Qt::Uninitialized);
    frame.SerializeToArray(blob.data(), blob.size());

    frame.release_keepalive();

    return blob;
}

QByteArray CiphrMailProtoCodec::encodeReady(bool locked)
{
    Ready ready;
    ClientFrame frame;

    ready.set_locked(locked);
    frame.set_allocated_ready(&ready);

    QByteArray blob(frame.ByteSize(), Qt::Uninitialized);
    frame.SerializeToArray(blob.data(), blob.size());

    frame.release_ready();

    return blob;
}

QByteArray CiphrMailProtoCodec::encodeAck(quint64 seq)
{
    Ack ack;
    ClientFrame frame;

    ack.set_seq(seq);
    frame.set_allocated_ack(&ack);

    QByteArray blob(frame.ByteSize(), Qt::Uninitialized);
    frame.SerializeToArray(blob.data(), blob.size());

    frame.release_ack();

    return blob;
}

void CiphrMailProtoCodec::decodeServerFrame(const QByteArray &blob)
{
    ServerFrame frame;
    frame.ParseFromArray(blob.constData(), blob.length());

    if (frame.has_pending()) {
        auto emails = frame.pending().emails();
        emit decodedPending(emails);
    }

    if (frame.has_serverkeepalive()) {
        emit decodedKeepAlive();
    }

    if (frame.has_hello()) {
        auto authenticated = frame.hello().authenticated();
        auto message = QString::fromStdString(frame.hello().message());
        emit decodedServerHello(authenticated, message);
    }

    if (frame.has_push_message()) {
        auto seq = frame.push_message().seq();
        auto envelope = frame.push_message().envelope();

        if (envelope.has_email()) {
            auto uid = QString::fromStdString(envelope.email().uid());
            auto displayTime = envelope.email().display_time();
            auto body = QByteArray::fromStdString(envelope.email().body());
            emit decodedEmail(seq, uid, displayTime, body);
        }

        if (envelope.has_receipt()) {
            auto id = QString::fromStdString(envelope.receipt().id());
            auto receiptType = envelope.receipt().type();
            if (receiptType == Receipt_ReceiptType_DELIVERY) {
                emit decodedDeliveryReceipt(seq, id);
            } else if (receiptType == Receipt_ReceiptType_READ) {
                emit decodedReadReceipt(seq, id);
            }
        }
    }
}
