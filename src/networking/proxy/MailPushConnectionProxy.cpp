#include "MailPushConnectionProxy.hpp"

MailPushConnectionProxy::MailPushConnectionProxy(
        gsl::not_null<AbstractMailPushConnection*> connection,
        QObject *parent)
    : AbstractMailPushConnection(parent)
    , _connection(connection.get())
{
    connect(_connection, &AbstractMailPushConnection::deliveryReceiptReceived, this, &AbstractMailPushConnection::deliveryReceiptReceived);
    connect(_connection, &AbstractMailPushConnection::readReceiptReceived, this, &AbstractMailPushConnection::readReceiptReceived);
    connect(_connection, &AbstractMailPushConnection::mailReceived, this, &AbstractMailPushConnection::mailReceived);
    connect(_connection, &AbstractMailPushConnection::pendingReceived, this, &AbstractMailPushConnection::pendingReceived);

    connect(_connection, &AbstractMailPushConnection::authenticating, this, &AbstractMailPushConnection::authenticating);
    connect(_connection, &AbstractMailPushConnection::connecting, this, &AbstractMailPushConnection::connecting);
    connect(_connection, &AbstractMailPushConnection::disconnected, this, &AbstractMailPushConnection::disconnected);
    connect(_connection, &AbstractMailPushConnection::error, this, &AbstractMailPushConnection::error);
    connect(_connection, &AbstractMailPushConnection::locked, this, &AbstractMailPushConnection::locked);
    connect(_connection, &AbstractMailPushConnection::unlocked, this, &AbstractMailPushConnection::unlocked);
}

bool MailPushConnectionProxy::hasFullCredentials() const
{
    return _connection->hasFullCredentials();
}

void MailPushConnectionProxy::open(const QString &email, const QString &password, const CiphrMailProtoCodec::ClientInfo &clientInfo)
{
    QMetaObject::invokeMethod(_connection, [=]{
        _connection->open(email, password, clientInfo);
    },
    Qt::QueuedConnection);
}

void MailPushConnectionProxy::open(const QString &token, const CiphrMailProtoCodec::ClientInfo &clientInfo)
{
    QMetaObject::invokeMethod(_connection, [=]{
        _connection->open(token, clientInfo);
    },
    Qt::QueuedConnection);
}

void MailPushConnectionProxy::close()
{
    QMetaObject::invokeMethod(_connection, &AbstractMailPushConnection::close, Qt::QueuedConnection);
}

void MailPushConnectionProxy::abort()
{
    QMetaObject::invokeMethod(_connection, &AbstractMailPushConnection::abort, Qt::QueuedConnection);
}

void MailPushConnectionProxy::lock()
{
    QMetaObject::invokeMethod(_connection, &AbstractMailPushConnection::lock, Qt::QueuedConnection);
}

void MailPushConnectionProxy::unlock()
{
    QMetaObject::invokeMethod(_connection, &AbstractMailPushConnection::unlock, Qt::QueuedConnection);
}

void MailPushConnectionProxy::ack(quint64 ack)
{
    QMetaObject::invokeMethod(_connection, [=]{
        _connection->ack(ack);
    },
    Qt::QueuedConnection);
}
