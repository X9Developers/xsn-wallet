#ifndef MAILPUSHCONNECTIONADAPTER_HPP
#define MAILPUSHCONNECTIONADAPTER_HPP

#include <AbstractMailPushConnection.hpp>
#include <gsl/gsl>

class MailPushConnectionImpl;

class MailPushConnectionAdapter : public AbstractMailPushConnection
{
    Q_OBJECT

public:
    MailPushConnectionAdapter(gsl::not_null<MailPushConnectionImpl*> impl, QObject *parent = nullptr);

public:
    bool hasFullCredentials() const override;

public slots:
    void open(const QString &email, const QString &password, const CiphrMailProtoCodec::ClientInfo &clientInfo) override;
    void open(const QString &token, const CiphrMailProtoCodec::ClientInfo &clientInfo) override;
    void close() override;
    void abort() override;
    void lock() override;
    void unlock() override;
    void ack(quint64 ack) override;

private:
    MailPushConnectionImpl *_impl;
};

#endif // MAILPUSHCONNECTIONADAPTER_HPP
