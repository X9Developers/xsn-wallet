#ifndef PORTALHTTPCLIENTIMPL_H
#define PORTALHTTPCLIENTIMPL_H

#include <QObject>
#include <QNetworkReply>
#include "AbstractPortalHttpClient.hpp"
#include "AbstractRequestHandler.hpp"

#include <gsl/gsl>

class PortalHttpClientImpl: public AbstractPortalHttpClient
{
    Q_OBJECT

public:
    PortalHttpClientImpl(gsl::not_null<AbstractRequestHandler*> requestHandler, QObject *parent = nullptr);

public slots:
    void sendActivateRequest(const QString &imei, const QString &code) override;
    void sendActivateCompletedRequest(const QString &token) override;
    void sendGetMyAccountRequest(const QString &token) override;

private:
    AbstractRequestHandler *_requestHandler;
};

#endif // PORTALHTTPCLIENTIMPL_H
