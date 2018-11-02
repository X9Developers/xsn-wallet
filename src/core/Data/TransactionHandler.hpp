#ifndef TransactionHandler_HPP
#define TransactionHandler_HPP

#include <QObject>
#include <QNetworkReply>
#include "RequestHandlerImpl.hpp"

class TransactionHandler : public QObject
{
    Q_OBJECT
public:
     TransactionHandler(QObject *parent = nullptr);
     virtual ~TransactionHandler();

signals:
     void transactionByAddressFailed(QString address, int errorCode, QString errorString);
     void transactionByAddressFinished(QString address, QByteArray response);

public slots:
    void getTransactionsByAddress(QString address);

private:
    RequestHandlerImpl *_requestHandler;
};


#endif // TransactionHandler_HPP
