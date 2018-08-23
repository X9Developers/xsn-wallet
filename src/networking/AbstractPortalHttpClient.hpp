#ifndef ABSTRACTPORTALHTTPCLIENT_HPP
#define ABSTRACTPORTALHTTPCLIENT_HPP

#include <QObject>

class AbstractPortalHttpClient: public QObject
{
    Q_OBJECT

public:
    explicit AbstractPortalHttpClient(QObject *parent = nullptr);

public:
    virtual void sendActivateRequest(const QString &imei, const QString &code) = 0;
    virtual void sendActivateCompletedRequest(const QString &token) = 0;
    virtual void sendGetMyAccountRequest(const QString &token) = 0;

signals:
    void activateFinished(const QString &id, const QString &email, const QString &password, const QString &token);
    void activateFailed(int errorCode, const QString &error);

    void activateCompletedFinished();
    void activateCompletedFailed(int errorCode, const QString &error);

    void getMyAccountFinished(const QVariantMap &response);
    void getMyAccountFailed(int errorCode, const QString &error);
};

#endif // ABSTRACTPORTALHTTPCLIENT_HPP
