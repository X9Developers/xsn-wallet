#ifndef BASEPUSHCONNECTION_HPP
#define BASEPUSHCONNECTION_HPP

#include <QObject>
#include <QList>
#include <QSslError>
#include <QAbstractSocket>
#include <QLoggingCategory>
#include <QStateMachine>
#include <CiphrNetworkSettings.hpp>
#include <codec/FrameLengthCodec.hpp>

class QTimer;
class QSslSocket;

class BasePushConnection : public QObject
{
    Q_OBJECT

public slots:
    void close();
    void abort();
    void lock();
    void unlock();
    void ack(quint64 ack);

signals:
    void connecting();
    void authenticating();
    void locked();
    void unlocked();
    void disconnected();
    void error(const QString& message);

protected:
    explicit BasePushConnection(
        const CiphrNetworkSettings::PushServerSettings &settings,
        QSharedPointer<FrameLengthCodec> codec,
        const char *logPrefix,
        QObject *parent = nullptr
    );
    virtual ~BasePushConnection();

    virtual QByteArray getKeepAliveFrame() = 0;
    virtual QByteArray getLockUpdateFrame(bool locked) = 0;
    virtual QByteArray getAckFrame(quint64 ack) = 0;
    virtual void handleReceivedFrame(const QByteArray &frame) = 0;

    void dial(const QByteArray &helloFrame);
    void write(const QByteArray &frame);
    void authenticate(bool success);
    void confirmKeepAlive();

private slots:
    void reconnect();
    void reconnectLater();
    void sendKeepAlive();
    void dialTimeout();
    void readyRead();
    void socketStateChanged(QAbstractSocket::SocketState);
    void socketSslErrors(const QList<QSslError>&);
    void socketError(QAbstractSocket::SocketError);
    void socketEncrypted();
    void handleConnectingState();
    void handleAuthenticatingState();

private:
    void createStates();
    void setupTransitions();
    void disconnect(bool abort = false);

    CiphrNetworkSettings::PushServerSettings _settings;
    QSharedPointer<FrameLengthCodec> _codec;
    QSslSocket *_socket;
    QByteArray _buffer;
    QLoggingCategory _logCategory;
    QByteArray _helloFrame;
    QTimer *_dialTimer;
    QTimer *_keepAliveTimer;
    QTimer *_reconnectTimer;
    int _length {0};
    int _offset {0};
    bool _waitingKeepAlive {false};
    QStateMachine *_stateMachine {nullptr};
    QState *_disconnectedState {nullptr};
    QState *_connectingState {nullptr};
    QState *_authenticatingState {nullptr};
    QState *_connectedAndLockedState {nullptr};
    QState *_connectedAndUnlockedState {nullptr};
};

#endif // BASEPUSHCONNECTION_HPP
