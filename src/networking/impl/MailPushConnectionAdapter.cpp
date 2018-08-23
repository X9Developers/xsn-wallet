#include "MailPushConnectionAdapter.hpp"
#include "MailPushConnectionImpl.hpp"

MailPushConnectionAdapter::MailPushConnectionAdapter(gsl::not_null<MailPushConnectionImpl *> impl, QObject *parent)
    : AbstractMailPushConnection(parent)
    , _impl(impl)
{
    connect(_impl, &MailPushConnectionImpl::deliveryReceiptReceived, this, &MailPushConnectionAdapter::deliveryReceiptReceived);
    connect(_impl, &MailPushConnectionImpl::readReceiptReceived, this, &MailPushConnectionAdapter::readReceiptReceived);
    connect(_impl, &MailPushConnectionImpl::mailReceived, this, &MailPushConnectionAdapter::mailReceived);
    connect(_impl, &MailPushConnectionImpl::pendingReceived, this, &MailPushConnectionAdapter::pendingReceived);

    connect(_impl, &MailPushConnectionImpl::authenticating, this, &MailPushConnectionAdapter::authenticating);
    connect(_impl, &MailPushConnectionImpl::connecting, this, &MailPushConnectionAdapter::connecting);
    connect(_impl, &MailPushConnectionImpl::disconnected, this, &MailPushConnectionAdapter::disconnected);
    connect(_impl, &MailPushConnectionImpl::error, this, &MailPushConnectionAdapter::error);
    connect(_impl, &MailPushConnectionImpl::locked, this, &MailPushConnectionAdapter::locked);
    connect(_impl, &MailPushConnectionImpl::unlocked, this, &MailPushConnectionAdapter::unlocked);
}

bool MailPushConnectionAdapter::hasFullCredentials() const
{
    return _impl->hasFullCredentials();
}

void MailPushConnectionAdapter::open(const QString &email, const QString &password, const CiphrMailProtoCodec::ClientInfo &clientInfo)
{
    _impl->open(email, password, clientInfo);
}

void MailPushConnectionAdapter::open(const QString &token, const CiphrMailProtoCodec::ClientInfo &clientInfo)
{
    _impl->open(token, clientInfo);
}

void MailPushConnectionAdapter::close()
{
    _impl->close();
}

void MailPushConnectionAdapter::abort()
{
    _impl->abort();
}

void MailPushConnectionAdapter::lock()
{
    _impl->lock();
}

void MailPushConnectionAdapter::unlock()
{
    _impl->unlock();
}

void MailPushConnectionAdapter::ack(quint64 ack)
{
    _impl->ack(ack);
}
