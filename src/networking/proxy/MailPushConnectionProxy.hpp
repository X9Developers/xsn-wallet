#ifndef MAILPUSHCONNECTIONPROXY_HPP
#define MAILPUSHCONNECTIONPROXY_HPP

#include <QObject>
#include <AbstractMailPushConnection.hpp>
#include <codec/CiphrMailProtoCodec.hpp>
#include <gsl/gsl>

class MailPushConnectionProxy : public AbstractMailPushConnection
{
    Q_OBJECT

public:
    MailPushConnectionProxy(gsl::not_null<AbstractMailPushConnection*> connection,
                            QObject *parent = nullptr);

    bool hasFullCredentials() const override;

public slots:
    void open(const QString& email, const QString& password, const CiphrMailProtoCodec::ClientInfo &clientInfo) override;
    void open(const QString& token, const CiphrMailProtoCodec::ClientInfo &clientInfo) override;
    void close() override;
    void abort() override;
    void lock() override;
    void unlock() override;
    void ack(quint64 ack) override;

private:
    AbstractMailPushConnection *_connection;
};

#endif // MAILPUSHCONNECTIONPROXY_HPP
