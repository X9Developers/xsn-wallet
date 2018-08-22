#ifndef REQUESTHANDLERIMPL_H
#define REQUESTHANDLERIMPL_H

#include <QNetworkReply>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonArray>
#include <functional>
#include <gsl/gsl>

#include <CiphrNetworkSettings.hpp>
#include <AbstractRequestHandler.hpp>

class RequestHandlerImpl : public AbstractRequestHandler
{
    Q_OBJECT

public:
    using ResponseHandler = std::function<void(const QByteArray&, const HttpHeaders&)>;
    using NetworkErrorHandler = std::function<void(int, const QString&)>;
    using RequestMaker = std::function<QNetworkReply*()>;

public:
    RequestHandlerImpl(const CiphrNetworkSettings::HttpServerSettings &settings,
                       gsl::not_null<QNetworkAccessManager*> networkManager,
                       QObject *parent = nullptr);

    void makeHeadRequest(const QString &path,
                         const QVariantMap &params,
                         NetworkErrorHandler errorHandler,
                         ResponseHandler responseHandler,
                         int retryAttempts = 0) override;

    void makeGetRequest(const QString &path,
                        const QVariantMap &params,
                        NetworkErrorHandler errorHandler,
                        ResponseHandler responseHandler,
                        const HttpRange &range,
                        int retryAttempts = 0) override;

    // post as url-encoded
    void makePostRequest(const QString &path,
                         const QVariantMap &params,
                         NetworkErrorHandler errorHandler,
                         ResponseHandler responseHandler,
                         int retryAttempts = 0) override;

    // post as json
    void makePostRequest(const QString &path,
                         const QJsonDocument &body,
                         NetworkErrorHandler errorHandler,
                         ResponseHandler responseHandler,
                         int retryAttempts = 0) override;

    // post as raw bytes
    void makePostRequest(const QString &path,
                         const QVariantMap &params,
                         const QByteArray &body,
                         NetworkErrorHandler errorHandler,
                         ResponseHandler responseHandler,
                         const HttpContentRange &range = HttpContentRange(),
                         int retryAttempts = 0) override;

private slots:
    void processResponse(QNetworkReply *reply,
                         NetworkErrorHandler errorHandler,
                         ResponseHandler responseHandler);

    void checkSslCertificate(const QList<QSslError> &errors);
    void configureRetries(RequestMaker requestMaker, QNetworkReply *reply, int retryAttempts);

private:
    void processNetworkReply(QNetworkReply *reply,
                             NetworkErrorHandler errorHandler,
                             ResponseHandler responseHandler);

    QUrl buildUrl(const QString &path, const QVariantMap &params = QVariantMap());

    CiphrNetworkSettings::HttpServerSettings _settings;
    QNetworkAccessManager *_networkAccessManager;
};

#endif // REQUESTHANDLERIMPL_H
