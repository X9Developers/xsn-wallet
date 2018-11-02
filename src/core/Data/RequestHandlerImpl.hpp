#ifndef REQUESTHANDLERIMPL_HPP
#define REQUESTHANDLERIMPL_HPP

#include <QNetworkReply>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonArray>
#include <functional>

class RequestHandlerImpl : public QObject
{
    Q_OBJECT
public:
    using ResponseHandler = std::function<void(const QByteArray&)>;
    using NetworkErrorHandler = std::function<void(int, const QString&)>;
    using RequestMaker = std::function<QNetworkReply*()>;

public:
    RequestHandlerImpl(QNetworkAccessManager* networkManager,
                       QObject *parent = nullptr);
    virtual ~RequestHandlerImpl();

    void makeGetRequest(const QString &path,
                        const QVariantMap &params,
                        NetworkErrorHandler errorHandler,
                        ResponseHandler responseHandler,
                        int retryAttempts = 0);

private slots:
    void processResponse(QNetworkReply *reply,
                         NetworkErrorHandler errorHandler,
                         ResponseHandler responseHandler);

private:
    void processRequest(RequestMaker requestMaker,
                        NetworkErrorHandler errorHandler,
                        ResponseHandler responseHandler,
                        int retryAttempts = 1);

    QUrl buildUrl(const QString &path, const QVariantMap &params = QVariantMap());

    QNetworkAccessManager *_networkAccessManager;
};

#endif // REQUESTHANDLERIMPL_HPP
