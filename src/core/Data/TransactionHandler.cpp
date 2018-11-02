#include "TransactionHandler.hpp"
#include <QJsonObject>
#include <QJsonDocument>
#include "RequestHandlerImpl.hpp"

//==============================================================================

TransactionHandler::TransactionHandler(QObject *parent) :
    QObject(parent)
{
    auto manager = new QNetworkAccessManager(this);
    _requestHandler = new RequestHandlerImpl(manager);
}

//==============================================================================

TransactionHandler::~TransactionHandler()
{

}

//==============================================================================

void TransactionHandler::getTransactionsByAddress(QString address)
{
    Q_ASSERT(!address.isEmpty());

    auto errorHandler = [=](int errorCode, const QString &errorString){
        emit transactionByAddressFailed(address, errorCode, errorString);
    };

    QString offset;
    QString limit;
    QString orderBy;

    auto responseHandler = [&](const QByteArray &response) {
         QJsonObject json = QJsonDocument::fromJson(response).object();

//         offset = json.value("offset").toString();
//         limit = json.value("limit").toString();
//         orderBy = json.value("orderBy").toString();

         QJsonObject data = json.value("data").toObject();

        emit transactionByAddressFinished(address, response);
    };

    QVariantMap params = {
        {"offset", offset},
        {"limit", limit},
        {"orderBy", orderBy}
    };

    const QString url = QString("addresses/%1/transactions").arg(QString(QUrl::toPercentEncoding(address)));
    _requestHandler->makeGetRequest(url, {}, errorHandler, responseHandler);
}

//==============================================================================
