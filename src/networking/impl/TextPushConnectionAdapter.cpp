#include "TextPushConnectionAdapter.hpp"
#include "TextPushConnectionImpl.hpp"

TextPushConnectionAdapter::TextPushConnectionAdapter(gsl::not_null<TextPushConnectionImpl *> impl, QObject *parent)
    : AbstractTextPushConnection(parent)
    , _impl(impl)
{
    connect(_impl, &TextPushConnectionImpl::broadcastReceived, this, &TextPushConnectionAdapter::broadcastReceived);
    connect(_impl, &TextPushConnectionImpl::notifyReceived, this, &TextPushConnectionAdapter::notifyReceived);
    connect(_impl, &TextPushConnectionImpl::messageReceived, this, &TextPushConnectionAdapter::messageReceived);
    connect(_impl, &TextPushConnectionImpl::pendingReceived, this, &TextPushConnectionAdapter::pendingReceived);

    connect(_impl, &TextPushConnectionImpl::authenticating, this, &TextPushConnectionAdapter::authenticating);
    connect(_impl, &TextPushConnectionImpl::connecting, this, &TextPushConnectionAdapter::connecting);
    connect(_impl, &TextPushConnectionImpl::disconnected, this, &TextPushConnectionAdapter::disconnected);
    connect(_impl, &TextPushConnectionImpl::error, this, &TextPushConnectionAdapter::error);
    connect(_impl, &TextPushConnectionImpl::locked, this, &TextPushConnectionAdapter::locked);
    connect(_impl, &TextPushConnectionImpl::unlocked, this, &TextPushConnectionAdapter::unlocked);
}

bool TextPushConnectionAdapter::hasFullCredentials() const
{
    return _impl->hasFullCredentials();
}

void TextPushConnectionAdapter::open(const QString &pin, const QString &token)
{
    _impl->open(pin, token);
}

void TextPushConnectionAdapter::open(const QString &token)
{
    _impl->open(token);
}

void TextPushConnectionAdapter::broadcast(const QList<QString> &pins, const QByteArray &message)
{
    _impl->broadcast(pins, message);
}

void TextPushConnectionAdapter::send(quint64 seq, const QString &pin, const QByteArray &message, bool notify, const QString &notifyId)
{
    _impl->send(seq, pin, message, notify, notifyId);
}

void TextPushConnectionAdapter::close()
{
    _impl->close();
}

void TextPushConnectionAdapter::abort()
{
    _impl->abort();
}

void TextPushConnectionAdapter::lock()
{
    _impl->lock();
}

void TextPushConnectionAdapter::unlock()
{
    _impl->unlock();
}

void TextPushConnectionAdapter::ack(quint64 ack)
{
    _impl->ack(ack);
}
