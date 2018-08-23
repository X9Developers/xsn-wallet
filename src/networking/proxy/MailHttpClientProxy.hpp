#ifndef MAILHTTPCLIENTPROXY_HPP
#define MAILHTTPCLIENTPROXY_HPP

#include <QObject>
#include <AbstractMailHttpClient.hpp>

#include <gsl/gsl>

class MailHttpClientProxy : public AbstractMailHttpClient
{
    Q_OBJECT

public:
    MailHttpClientProxy(gsl::not_null<AbstractMailHttpClient*> client, QObject *parent = nullptr);

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
    AbstractMailHttpClient *_client;
};

#endif // MAILHTTPCLIENTPROXY_HPP
