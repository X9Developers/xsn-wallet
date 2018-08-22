#ifndef MAILHTTPCLIENTIMPL_HPP
#define MAILHTTPCLIENTIMPL_HPP

#include <QObject>
#include <AbstractRequestHandler.hpp>
#include <AbstractMailHttpClient.hpp>

#include <gsl/gsl>

class MailHttpClientImpl : public AbstractMailHttpClient
{
    Q_OBJECT

public:
    MailHttpClientImpl(gsl::not_null<AbstractRequestHandler*> requestHandler, QObject *parent = nullptr);

    void sendCreateMailboxRequest(const QString &email,
                                  const QString &password) override;
    void sendUploadRsaRequest(const QString &email,
                              const QString &password,
                              const QByteArray &rsaKey) override;
    void sendUploadEccRequest(const QString &email,
                              const QString &password,
                              const QByteArray &eccKey) override;
    void sendUploadEcc448Request(const QString &email,
                                 const QString &password,
                                 const QByteArray &ecc448Key) override;
    void sendEmailRequest(const QString &from,
                          const QString &password,
                          const QString &receiptId,
                          const QStringList &recipients,
                          const QByteArray &body) override;
    void sendSearchKeysRequest(const QString &email) override;

private:
    void uploadKey(const QString &url,
                   const QString &email,
                   const QString &password,
                   const QByteArray &ecc448Key,
                   AbstractRequestHandler::NetworkErrorHandler errorHandler,
                   AbstractRequestHandler::ResponseHandler responseHandler);

private:
    AbstractRequestHandler *_requestHandler;
};

#endif // MAILHTTPCLIENTIMPL_HPP
