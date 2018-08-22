#ifndef TEXTPUSHCONNECTIONPROXY_HPP
#define TEXTPUSHCONNECTIONPROXY_HPP

#include <QObject>
#include <AbstractTextPushConnection.hpp>
#include <gsl/gsl>

class TextPushConnectionProxy : public AbstractTextPushConnection
{
    Q_OBJECT

public:
    TextPushConnectionProxy();

public:
    TextPushConnectionProxy(gsl::not_null<AbstractTextPushConnection*> connection,
                            QObject *parent = nullptr);

    bool hasFullCredentials() const override;

public slots:
    void open(const QString &pin, const QString &token) override;
    void open(const QString &token) override;
    void broadcast(const QList<QString> &pins, const QByteArray &message) override;
    void send(quint64 seq, const QString &pin, const QByteArray &message, bool notify, const QString &notifyId) override;
    void close() override;
    void abort() override;
    void lock() override;
    void unlock() override;
    void ack(quint64 ack) override;

private:
    AbstractTextPushConnection *_connection;
};

#endif // TEXTPUSHCONNECTIONPROXY_HPP
