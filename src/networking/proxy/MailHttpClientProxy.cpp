#include "MailHttpClientProxy.hpp"

MailHttpClientProxy::MailHttpClientProxy(gsl::not_null<AbstractMailHttpClient*> client, QObject *parent)
    : AbstractMailHttpClient(parent)
    , _client(client)
{
    connect(_client, &AbstractMailHttpClient::createMailboxFailed, this, &MailHttpClientProxy::createMailboxFailed);
    connect(_client, &AbstractMailHttpClient::createMailboxFinished, this, &MailHttpClientProxy::createMailboxFinished);
    connect(_client, &AbstractMailHttpClient::searchFailed, this, &MailHttpClientProxy::searchFailed);
    connect(_client, &AbstractMailHttpClient::searchFinished, this, &MailHttpClientProxy::searchFinished);
    connect(_client, &AbstractMailHttpClient::sendEmailFailed, this, &MailHttpClientProxy::sendEmailFailed);
    connect(_client, &AbstractMailHttpClient::sendEmailFinished, this, &MailHttpClientProxy::sendEmailFinished);
    connect(_client, &AbstractMailHttpClient::uploadRsaFailed, this, &MailHttpClientProxy::uploadRsaFailed);
    connect(_client, &AbstractMailHttpClient::uploadRsaFinished, this, &MailHttpClientProxy::uploadRsaFinished);
    connect(_client, &AbstractMailHttpClient::uploadEccFailed, this, &MailHttpClientProxy::uploadEccFailed);
    connect(_client, &AbstractMailHttpClient::uploadEccFinished, this, &MailHttpClientProxy::uploadEccFinished);
    connect(_client, &AbstractMailHttpClient::uploadEcc448Failed, this, &MailHttpClientProxy::uploadEcc448Failed);
    connect(_client, &AbstractMailHttpClient::uploadEcc448Finished, this, &MailHttpClientProxy::uploadEcc448Finished);
}

void MailHttpClientProxy::sendCreateMailboxRequest(const QString &email, const QString &password)
{
    Q_ASSERT(!email.isEmpty());
    Q_ASSERT(!password.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
       _client->sendCreateMailboxRequest(email, password);
    },
    Qt::QueuedConnection);
}

void MailHttpClientProxy::sendUploadRsaRequest(const QString &email, const QString &password, const QByteArray &rsaKey)
{
    Q_ASSERT(!email.isEmpty());
    Q_ASSERT(!password.isEmpty());
    Q_ASSERT(!rsaKey.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
       _client->sendUploadRsaRequest(email, password, rsaKey);
    },
    Qt::QueuedConnection);
}

void MailHttpClientProxy::sendUploadEccRequest(const QString &email, const QString &password, const QByteArray &eccKey)
{
    Q_ASSERT(!email.isEmpty());
    Q_ASSERT(!password.isEmpty());
    Q_ASSERT(!eccKey.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
       _client->sendUploadEccRequest(email, password, eccKey);
    },
    Qt::QueuedConnection);
}

void MailHttpClientProxy::sendUploadEcc448Request(const QString &email, const QString &password, const QByteArray &ecc448Key)
{
    Q_ASSERT(!email.isEmpty());
    Q_ASSERT(!password.isEmpty());
    Q_ASSERT(!ecc448Key.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
       _client->sendUploadEcc448Request(email, password, ecc448Key);
    },
    Qt::QueuedConnection);
}

void MailHttpClientProxy::sendEmailRequest(const QString &from,
                                      const QString &password,
                                      const QString &receiptId,
                                      const QStringList &recipients,
                                      const QByteArray &body)
{
    Q_ASSERT(!from.isEmpty());
    Q_ASSERT(!password.isEmpty());
    Q_ASSERT(recipients.size() > 0);

    QMetaObject::invokeMethod(_client, [=](){
       _client->sendEmailRequest(from, password, receiptId, recipients, body);
    },
    Qt::QueuedConnection);
}

void MailHttpClientProxy::sendSearchKeysRequest(const QString &email)
{
    Q_ASSERT(!email.isEmpty());

    QMetaObject::invokeMethod(_client, [=](){
       _client->sendSearchKeysRequest(email);
    },
    Qt::QueuedConnection);
}
