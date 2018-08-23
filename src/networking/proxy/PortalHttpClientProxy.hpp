#ifndef PORTALHTTPCLIENTPROXY_H
#define PORTALHTTPCLIENTPROXY_H

#include <QObject>
#include <AbstractPortalHttpClient.hpp>

#include <gsl/gsl>

class PortalHttpClientProxy: public AbstractPortalHttpClient
{
    Q_OBJECT

public:
    PortalHttpClientProxy(gsl::not_null<AbstractPortalHttpClient*> client, QObject *parent = nullptr);

public slots:
    void sendActivateRequest(const QString &imei, const QString &code) override;
    void sendActivateCompletedRequest(const QString &token) override;
    void sendGetMyAccountRequest(const QString &token) override;

private:
    AbstractPortalHttpClient *_client;
};

#endif // PORTALHTTPCLIENTPROXY_H
