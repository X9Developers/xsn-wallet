#include "BasePushConnection.hpp"

#include <QDebug>
#include <QTimer>
#include <QSslSocket>

#define WARNING qCWarning(_logCategory)
#define DEBUG qCDebug(_logCategory)

BasePushConnection::BasePushConnection(
        const CiphrNetworkSettings::PushServerSettings &settings,
        QSharedPointer<FrameLengthCodec> codec,
        const char *logPrefix,
        QObject *parent
)
    : QObject(parent)
    , _settings(settings)
    , _codec(codec)
    , _socket(new QSslSocket(this))
    , _logCategory(logPrefix)
    , _dialTimer(new QTimer(this))
    , _keepAliveTimer(new QTimer(this))
    , _reconnectTimer(new QTimer(this))
{
    qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");

    createStates();
    setupTransitions();

    connect(_socket, &QSslSocket::encrypted, this, &BasePushConnection::socketEncrypted);
    connect(_socket, &QSslSocket::disconnected, this, &BasePushConnection::disconnected);
    connect(_socket, &QSslSocket::readyRead, this, &BasePushConnection::readyRead);
    connect(_socket, &QSslSocket::stateChanged, this, &BasePushConnection::socketStateChanged);
    connect(_socket, QOverload<const QList<QSslError>&>::of(&QSslSocket::sslErrors), this, &BasePushConnection::socketSslErrors);
    connect(_socket, QOverload<QAbstractSocket::SocketError>::of(&QSslSocket::error), this, &BasePushConnection::socketError);

    connect(_dialTimer, &QTimer::timeout, this, &BasePushConnection::dialTimeout);
    connect(_keepAliveTimer, &QTimer::timeout, this, &BasePushConnection::sendKeepAlive);
    connect(_reconnectTimer, &QTimer::timeout, this, &BasePushConnection::reconnect);

    _dialTimer->setSingleShot(true);
    _dialTimer->setInterval(settings.connectTimeoutMs);
    _reconnectTimer->setSingleShot(true);
    _reconnectTimer->setInterval(settings.reconnectIntervalMs);
    _keepAliveTimer->setInterval(settings.heartbeatIntervalMs);
}

BasePushConnection::~BasePushConnection()
{
    disconnect();
}

void BasePushConnection::dial(const QByteArray &helloFrame)
{
    if (_socket->state() == QAbstractSocket::HostLookupState ||
        _socket->state() == QAbstractSocket::ConnectedState ||
        _socket->state() == QAbstractSocket::ConnectingState) {
        WARNING << "Connection is already connecting or connected.";
        return;
    }

    WARNING << "Connecting to" << _settings.host << ":" << _settings.port;

    _helloFrame = helloFrame;
    emit connecting();
}

void BasePushConnection::close()
{
    _helloFrame.clear();
    _reconnectTimer->stop();

    disconnect();
}

void BasePushConnection::abort()
{
    _helloFrame.clear();
    _reconnectTimer->stop();

    disconnect(true);
}

void BasePushConnection::disconnect(bool abort)
{
    _keepAliveTimer->stop();
    _dialTimer->stop();
    _reconnectTimer->stop();

    if (_socket->state() == QAbstractSocket::UnconnectedState) {
        return;
    }

    if (_socket->state() == QAbstractSocket::ConnectingState ||
        _socket->state() == QAbstractSocket::HostLookupState ||
        _socket->state() == QAbstractSocket::ClosingState ||
        abort) {
        _socket->abort();
    } else {
        _socket->disconnectFromHost();
    }
}

void BasePushConnection::lock()
{
    DEBUG << "Locking connection...";

    write(getLockUpdateFrame(true));
    emit locked();
}

void BasePushConnection::unlock()
{
    DEBUG << "Unlocking connection...";

    write(getLockUpdateFrame(false));
    emit unlocked();
}

void BasePushConnection::ack(quint64 ack)
{
    bool unlocked = _stateMachine->configuration().contains(_connectedAndUnlockedState);
    if (unlocked) {
        DEBUG << "Sending ack" << ack;
        write(getAckFrame(ack));
    } else {
        DEBUG << "Ack" << ack << "ignored due to locked state.";
    }
}

void BasePushConnection::write(const QByteArray &frame)
{
    if (_socket->state() != QAbstractSocket::ConnectedState) {
        WARNING << "Write is ignored due to disconnected state.";
        return;
    }

    if (frame.length() > _settings.maxFrameSize) {
        WARNING << "Write is ignored due to max frame size exceeded.";
        return;
    }

    QByteArray length = _codec->encodeLength(frame.length());
    _socket->write(length);
    _socket->write(frame);
}

void BasePushConnection::socketSslErrors(const QList<QSslError> &errors)
{
    DEBUG << "SSL errors:" << errors;

    _socket->ignoreSslErrors();

    auto sha1Digest = _socket->peerCertificate().digest(QCryptographicHash::Sha1);
    if (sha1Digest != _settings.sha1Digest) {
        DEBUG << "Peer certificate digest:" << sha1Digest.toHex();
        emit error(tr("Connecting aborted due to untrusted host."));
        close();
    }
}

void BasePushConnection::socketError(QAbstractSocket::SocketError)
{
    WARNING << "Socket error" << _socket->errorString();

    emit error(_socket->errorString());

    bool authenticating = _stateMachine->configuration().contains(_authenticatingState);
    if (authenticating) {
        abort();
    } else {
        reconnectLater();
    }
}

void BasePushConnection::dialTimeout()
{
    DEBUG << Q_FUNC_INFO;

    if (_socket->state() != QAbstractSocket::ConnectedState) {
        DEBUG << "Failed to connect within" << _settings.connectTimeoutMs << "ms.";
        emit error(tr("Connection timeout."));
        reconnectLater();
    }
}

void BasePushConnection::socketStateChanged(QAbstractSocket::SocketState state)
{
    DEBUG << "Socket state changed" << state;
}

void BasePushConnection::readyRead()
{
    _buffer.append(_socket->readAll());

    do {
        if (_length == 0) {
            int offset;
            int length = _codec->decodeLength(_buffer, &offset);
            if (length == -1) {
                break;
            }

            if (length > _settings.maxFrameSize) {
                emit error(tr("Connection received too large frame."));
                abort();
                break;
            }

            _length = length;
            _offset = offset;
        }

        if (_buffer.length() >= (_length + _offset)) {
            DEBUG << "Connection received a frame:" << _length << "bytes.";
            handleReceivedFrame(_buffer.mid(_offset, _length));

            _buffer = _buffer.right(_buffer.length() - _length - _offset);
            _length = 0;
            _offset = 0;
        } else {
            // no enough data to build the frame
            break;
        }
    }
    while (_buffer.length() > 0);
}

void BasePushConnection::socketEncrypted()
{
    _dialTimer->stop();
    emit authenticating();
}

void BasePushConnection::handleConnectingState()
{
    _socket->connectToHostEncrypted(_settings.host, _settings.port);
    if (_settings.connectTimeoutMs > 0) {
        _dialTimer->start();
    }
}

void BasePushConnection::handleAuthenticatingState()
{
    DEBUG << "Sending hello frame" << _helloFrame.size();
    write(_helloFrame);
}

void BasePushConnection::createStates()
{
    _stateMachine = new QStateMachine(this);
    _disconnectedState = new QState(_stateMachine);
    _connectingState = new QState(_stateMachine);
    _authenticatingState = new QState(_stateMachine);
    _connectedAndLockedState = new QState(_stateMachine);
    _connectedAndUnlockedState = new QState(_stateMachine);
}

void BasePushConnection::setupTransitions()
{
    _disconnectedState->addTransition(this, &BasePushConnection::connecting, _connectingState);
    _connectingState->addTransition(this, &BasePushConnection::authenticating, _authenticatingState);
    _connectingState->addTransition(this, &BasePushConnection::disconnected, _disconnectedState);
    _authenticatingState->addTransition(this, &BasePushConnection::unlocked, _connectedAndUnlockedState);
    _authenticatingState->addTransition(this, &BasePushConnection::locked, _connectedAndLockedState);
    _authenticatingState->addTransition(this, &BasePushConnection::disconnected, _disconnectedState);
    _connectedAndLockedState->addTransition(this, &BasePushConnection::unlocked, _connectedAndUnlockedState);
    _connectedAndLockedState->addTransition(this, &BasePushConnection::disconnected, _disconnectedState);
    _connectedAndUnlockedState->addTransition(this, &BasePushConnection::locked, _connectedAndLockedState);
    _connectedAndUnlockedState->addTransition(this, &BasePushConnection::disconnected, _disconnectedState);

    connect(_connectingState, &QState::entered, this, &BasePushConnection::handleConnectingState);
    connect(_authenticatingState, &QState::entered, this, &BasePushConnection::handleAuthenticatingState);
    connect(_disconnectedState, &QState::entered, this, &BasePushConnection::reconnectLater);

    _stateMachine->setInitialState(_disconnectedState);
    _stateMachine->start();
}

void BasePushConnection::authenticate(bool success)
{
    _reconnectTimer->stop();

    if (success) {
        _keepAliveTimer->start();
        confirmKeepAlive();
        sendKeepAlive();
    } else {
        close();
    }
}

void BasePushConnection::reconnect()
{
    if (_helloFrame.isEmpty()) {
        return;
    }

    auto helloFrame = _helloFrame;
    abort();

    WARNING << "Reconnecting...";
    dial(helloFrame);
}

void BasePushConnection::reconnectLater()
{
    if (_reconnectTimer->isActive()) {
        return;
    }

    _reconnectTimer->start();
}

void BasePushConnection::sendKeepAlive()
{
    if (!_keepAliveTimer->isActive()) {
        return;
    }

    if (_waitingKeepAlive) {
        WARNING << "Heartbeat broken, reconnecting...";
        reconnectLater();
    } else {
        DEBUG << "Sending KeepAlive...";
        _waitingKeepAlive = true;
        write(getKeepAliveFrame());
    }
}

void BasePushConnection::confirmKeepAlive()
{
    _waitingKeepAlive = false;
}
