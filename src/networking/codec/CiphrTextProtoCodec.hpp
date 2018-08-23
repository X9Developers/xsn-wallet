#ifndef CIPHRTEXTPROTOCODEC_HPP
#define CIPHRTEXTPROTOCODEC_HPP

#include <QObject>
#include <QByteArray>
#include <QString>

class CiphrTextProtoCodec : public QObject
{
    Q_OBJECT

public:
    explicit CiphrTextProtoCodec(QObject* parent = nullptr);

    QByteArray encodeHello(const QString &token, const QString &pin, bool locked);
    QByteArray encodeTokenAuth(const QString &token);
    QByteArray encodeAck(quint64 ack);
    QByteArray encodeKeepAlive();
    QByteArray encodeLockUpdate(bool locked);
    QByteArray encodeBroadcast(const QList<QString> &pins, const QByteArray &message);
    QByteArray encodeSend(quint64 seq, const QString &pin, const QByteArray &message, bool notify, const QString &notifyId);

    void decodeServerFrame(const QByteArray &blob);

signals:
    void decodedServerHello(const QString &message);
    void decodedServerAck(quint64 ack);
    void decodedKeepAlive();
    void decodedPending(quint32 notifications);
    void decodedReceived(quint64 seq, const QString &pin, const QByteArray &message);
    void decodedReceivedNotify(quint64 seq, const QString &pin, const QString &notifyId);
    void decodedReceivedBroadcast(const QString &pin, const QByteArray &message);
};

#endif // CIPHRTEXTPROTOCODEC_HPP
