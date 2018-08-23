#include "PortalHttpClientImpl.hpp"
#include <QJsonObject>
#include <QJsonDocument>
#include <JsonUtils.h>

PortalHttpClientImpl::PortalHttpClientImpl(gsl::not_null<AbstractRequestHandler*> requestHandler, QObject *parent)
    : AbstractPortalHttpClient(parent)
    , _requestHandler(requestHandler)
{
}

void PortalHttpClientImpl::sendActivateRequest(const QString &imei, const QString &code)
{
    Q_ASSERT(!imei.isEmpty());
    Q_ASSERT(!code.isEmpty());

    QJsonDocument requestBody {
        QJsonObject {
            {"imei", imei},
            {"code", code}
        }
    };

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit activateFailed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray &response, const AbstractRequestHandler::HttpHeaders&) {
        bool ok;
        QJsonObject json = JsonUtils::parseJsonObject(response, &ok);

        if (ok && json.contains("error")) {
            emit activateFailed(json["error"].toInt(-1), json["errorMessage"].toString());
            return;
        }

        if (!ok ||
            !json.contains("id") ||
            !json.contains("email") ||
            !json.contains("password") ||
            !json.contains("account_token"))
        {
            emit activateFailed(-1, tr("Bad server response format."));
            return;
        }

        emit activateFinished(
                    json["id"].toString(),
                    json["email"].toString(),
                    json["password"].toString(),
                    json["account_token"].toString());
    };

    _requestHandler->makePostRequest("as1/service/activate", requestBody, errorHandler, responseHandler);
}

void PortalHttpClientImpl::sendActivateCompletedRequest(const QString &token)
{
    Q_ASSERT(!token.isEmpty());

    QJsonDocument requestBody {
        QJsonObject {
            {"token", token}
        }
    };

    auto errorHandler = [this](int errorCode, const QString &errorString) {
        emit activateCompletedFailed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray &response, const AbstractRequestHandler::HttpHeaders&) {
        bool ok;
        QJsonObject json = JsonUtils::parseJsonObject(response, &ok);
        if (ok && json.contains("error")) {
            emit activateCompletedFailed(json["error"].toInt(-1), json["errorMessage"].toString());
        } else {
            emit activateCompletedFinished();
        }
    };

    _requestHandler->makePostRequest("as1/service/activate_completed", requestBody, errorHandler, responseHandler);
}

void PortalHttpClientImpl::sendGetMyAccountRequest(const QString &token)
{
    Q_ASSERT(!token.isEmpty());

    QJsonDocument requestBody {
        QJsonObject {
            {"token", token}
        }
    };

    auto errorHandler = [this](int errorCode, const QString &errorString){
        emit getMyAccountFailed(errorCode, errorString);
    };

    auto responseHandler = [this](const QByteArray &response, const AbstractRequestHandler::HttpHeaders&) {
        bool ok;
        QJsonObject json = JsonUtils::parseJsonObject(response, &ok);
        if (ok) {
            if (json.contains("error")) {
                emit getMyAccountFailed(json["error"].toInt(-1), json["errorMessage"].toString());
            } else {
                emit getMyAccountFinished(json.toVariantMap());
            }
        } else {
            emit getMyAccountFailed(-1, tr("Bad server response format."));
        }
    };

    _requestHandler->makePostRequest("as1/service/my_account", requestBody, errorHandler, responseHandler);
}
