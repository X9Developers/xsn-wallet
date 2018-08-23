#ifndef ABSTRACTMAILHTTPCLIENT_HPP
#define ABSTRACTMAILHTTPCLIENT_HPP

#include <QObject>
#include <gsl/gsl>

class AbstractMailHttpClient : public QObject
{
    Q_OBJECT

public:
    static const int MAIL_EXIST_RESPONSE_CODE = 409;

public:
    explicit AbstractMailHttpClient(QObject *parent = nullptr);

public:
    virtual void sendCreateMailboxRequest(const QString &email,
                                          const QString &password) = 0;

    virtual void sendUploadRsaRequest(const QString &email,
                                      const QString &password,
                                      const QByteArray &rsaKey) = 0;

    virtual void sendUploadEccRequest(const QString &email,
                                      const QString &password,
                                      const QByteArray &eccKey) = 0;

    virtual void sendUploadEcc448Request(const QString &email,
                                         const QString &password,
                                         const QByteArray &ecc448Key) = 0;

    virtual void sendEmailRequest(const QString &from,
                                  const QString &password,
                                  const QString &receiptId,
                                  const QStringList &recipients,
                                  const QByteArray &body) = 0;

    virtual void sendSearchKeysRequest(const QString &email) = 0;

signals:
    void createMailboxFinished();
    void createMailboxFailed(int error, const QString &message);

    void uploadRsaFinished();
    void uploadRsaFailed(int error, const QString &message);

    void uploadEccFinished();
    void uploadEccFailed(int error, const QString &message);

    void uploadEcc448Finished();
    void uploadEcc448Failed(int error, const QString &message);

    void sendEmailFinished();
    void sendEmailFailed(int error, const QString &message);

    void searchFinished(const QString &email,
                        const QString &rsaKey,
                        const QString &ecc255Key,
                        const QString &ecc448Key);
    void searchFailed(const QString &email, int error, const QString &message);
};

#endif // ABSTRACTMAILHTTPCLIENT_HPP
