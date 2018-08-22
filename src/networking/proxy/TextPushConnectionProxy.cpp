#include "TextPushConnectionProxy.hpp"

TextPushConnectionProxy::TextPushConnectionProxy(
        gsl::not_null<AbstractTextPushConnection*> connection,
        QObject *parent)
    : AbstractTextPushConnection(parent)
    , _connection(connection.get())
{
    connect(_connection, &AbstractTextPushConnection::broadcastReceived, this, &AbstractTextPushConnection::broadcastReceived);
    connect(_connection, &AbstractTextPushConnection::notifyReceived, this, &AbstractTextPushConnection::notifyReceived);
    connect(_connection, &AbstractTextPushConnection::messageReceived, this, &AbstractTextPushConnection::messageReceived);
    connect(_connection, &AbstractTextPushConnection::pendingReceived, this, &AbstractTextPushConnection::pendingReceived);

    connect(_connection, &AbstractTextPushConnection::authenticating, this, &AbstractTextPushConnection::authenticating);
    connect(_connection, &AbstractTextPushConnection::connecting, this, &AbstractTextPushConnection::connecting);
    connect(_connection, &AbstractTextPushConnection::disconnected, this, &AbstractTextPushConnection::disconnected);
    connect(_connection, &AbstractTextPushConnection::error, this, &AbstractTextPushConnection::error);
    connect(_connection, &AbstractTextPushConnection::locked, this, &AbstractTextPushConnection::locked);
    connect(_connection, &AbstractTextPushConnection::unlocked, this, &AbstractTextPushConnection::unlocked);
}

bool TextPushConnectionProxy::hasFullCredentials() const
{
    return _connection->hasFullCredentials();
}

void TextPushConnectionProxy::open(const QString &pin, const QString &token)
{
    QMetaObject::invokeMethod(_connection, [=]{
        _connection->open(pin, token);
    },
    Qt::QueuedConnection);
}

void TextPushConnectionProxy::open(const QString &token)
{
    QMetaObject::invokeMethod(_connection, [=]{
        _connection->open(token);
    },
    Qt::QueuedConnection);
}

void TextPushConnectionProxy::broadcast(const QList<QString> &pins, const QByteArray &message)
{
    QMetaObject::invokeMethod(_connection, [=]{
        _connection->broadcast(pins, message);
    },
    Qt::QueuedConnection);
}

void TextPushConnectionProxy::send(quint64 seq, const QString &pin, const QByteArray &message, bool notify, const QString &notifyId)
{
    QMetaObject::invokeMethod(_connection, [=]{
        _connection->send(seq, pin, message, notify, notifyId);
    },
    Qt::QueuedConnection);
}

void TextPushConnectionProxy::close()
{
    QMetaObject::invokeMethod(_connection, &AbstractTextPushConnection::close, Qt::QueuedConnection);
}

void TextPushConnectionProxy::abort()
{
    QMetaObject::invokeMethod(_connection, &AbstractTextPushConnection::abort, Qt::QueuedConnection);
}

void TextPushConnectionProxy::lock()
{
    QMetaObject::invokeMethod(_connection, &AbstractTextPushConnection::lock, Qt::QueuedConnection);
}

void TextPushConnectionProxy::unlock()
{
    QMetaObject::invokeMethod(_connection, &AbstractTextPushConnection::unlock, Qt::QueuedConnection);
}

void TextPushConnectionProxy::ack(quint64 ack)
{
    QMetaObject::invokeMethod(_connection, [=]{
        _connection->ack(ack);
    },
    Qt::QueuedConnection);
}

