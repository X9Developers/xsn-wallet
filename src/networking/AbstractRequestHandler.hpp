#ifndef ABSTRACTREQUESTHANDLER_HPP
#define ABSTRACTREQUESTHANDLER_HPP

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonArray>
#include <functional>
#include <HttpRange.hpp>
#include <HttpContentRange.hpp>

class AbstractRequestHandler : public QObject
{
public:
    explicit AbstractRequestHandler(QObject *parent = nullptr);

public:
    struct HttpHeaders {
        QString contentType;
        QString contentFilename;
        QString acceptRanges;
        qint64 contentLength;
        HttpContentRange contentRange;
    };

    using ResponseHandler = std::function<void(const QByteArray&, const HttpHeaders&)>;
    using NetworkErrorHandler = std::function<void(int, const QString&)>;

public:
    virtual void makeHeadRequest(const QString &path,
                                 const QVariantMap &params,
                                 NetworkErrorHandler errorHandler,
                                 ResponseHandler responseHandler,
                                 int retryAttempts = 0) = 0;

    virtual void makeGetRequest(const QString &path,
                                const QVariantMap &params,
                                NetworkErrorHandler errorHandler,
                                ResponseHandler responseHandler,
                                const HttpRange &range = HttpRange(),
                                int retryAttempts = 0) = 0;

    // post as url-encoded
    virtual void makePostRequest(const QString &path,
                                 const QVariantMap &params,
                                 NetworkErrorHandler errorHandler,
                                 ResponseHandler responseHandler,
                                 int retryAttempts = 0) = 0;

    // post as json
    virtual void makePostRequest(const QString &path,
                                 const QJsonDocument &body,
                                 NetworkErrorHandler errorHandler,
                                 ResponseHandler responseHandler,
                                 int retryAttempts = 0) = 0;

    // post as raw bytes
    virtual void makePostRequest(const QString &path,
                                 const QVariantMap &params,
                                 const QByteArray &body,
                                 NetworkErrorHandler errorHandler,
                                 ResponseHandler responseHandler,
                                 const HttpContentRange &range = HttpContentRange(),
                                 int retryAttempts = 0) = 0;
};

#endif // ABSTRACTREQUESTHANDLER_HPP
