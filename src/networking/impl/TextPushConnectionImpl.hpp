#ifndef TEXTPUSHCONNECTIONIMPL_HPP
#define TEXTPUSHCONNECTIONIMPL_HPP

#include <QObject>
#include <impl/BasePushConnection.hpp>
#include <CiphrNetworkSettings.hpp>
#include <AbstractTextPushConnection.hpp>

class CiphrTextProtoCodec;

class TextPushConnectionImpl : public BasePushConnection
{
    Q_OBJECT

public:
    TextPushConnectionImpl(const CiphrNetworkSettings::PushServerSettings &settings, QObject *parent = nullptr);

    bool hasFullCredentials() const;

public slots:
    virtual void open(const QString& pin, const QString& token);
    virtual void open(const QString& token);
    void broadcast(const QList<QString> &pins, const QByteArray &message);
    void send(quint64 seq, const QString &pin, const QByteArray &message, bool notify, const QString &notifyId);

signals:
    void pendingReceived(quint32 notifications);
    void messageReceived(quint64 seq, const QString &pin, const QByteArray &message);
    void notifyReceived(quint64 seq, const QString &pin, const QString &notifyId);
    void broadcastReceived(const QString &pin, const QByteArray &message);

protected:
    QByteArray getKeepAliveFrame() override;
    QByteArray getLockUpdateFrame(bool locked) override;
    QByteArray getAckFrame(quint64 ack) override;
    void handleReceivedFrame(const QByteArray &frame) override;

private slots:
    void keepAliveReceived();
    void serverHelloReceived(const QString &message);

private:
    CiphrTextProtoCodec *_protoCodec;
    bool _fullCredentials;
};

#endif // TEXTPUSHCONNECTIONIMPL_HPP
