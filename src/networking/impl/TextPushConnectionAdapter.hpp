#ifndef TEXTPUSHCONNECTIONADAPTER_HPP
#define TEXTPUSHCONNECTIONADAPTER_HPP

#include <AbstractTextPushConnection.hpp>
#include <gsl/gsl>

class TextPushConnectionImpl;

class TextPushConnectionAdapter : public AbstractTextPushConnection
{
    Q_OBJECT

public:
    TextPushConnectionAdapter(gsl::not_null<TextPushConnectionImpl*> impl, QObject *parent = nullptr);

public:
    bool hasFullCredentials() const override;

public slots:
    void open(const QString& pin, const QString& token) override;
    void open(const QString& token) override;
    void broadcast(const QList<QString> &pins, const QByteArray &message) override;
    void send(quint64 seq, const QString &pin, const QByteArray &message, bool notify, const QString &notifyId) override;
    void close() override;
    void abort() override;
    void lock() override;
    void unlock() override;
    void ack(quint64 ack) override;

private:
    TextPushConnectionImpl *_impl;
};

#endif // TEXTPUSHCONNECTIONADAPTER_HPP
