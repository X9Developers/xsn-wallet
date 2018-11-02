#ifndef TST_PORTALHTTPCLIENT_HPP
#define TST_PORTALHTTPCLIENT_HPP

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QSignalSpy>
#include <QJsonObject>
#include <QJsonDocument>
#include "Data/TransactionHandler.hpp"

using namespace testing;

TEST(CoreTests, getTransactionsByAddress)
{
    TransactionHandler portalApi{};

    QSignalSpy spy(&portalApi, &TransactionHandler::transactionByAddressFinished);
    const QString address = "XvNBN8xe5twNu1qLh2M7ZgkjRY9sEeXpCx";
    portalApi.getTransactionsByAddress(address);

    spy.wait(2000);
    EXPECT_EQ(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    EXPECT_EQ(arguments.at(0).toInt(), 1);
    EXPECT_TRUE(arguments.at(1).toString().contains("5"));
}
#endif // TST_PORTALHTTPCLIENT_HPP
