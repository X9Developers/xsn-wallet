#include "AbstractTextHttpClient.hpp"

AbstractTextHttpClient::AbstractTextHttpClient(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<QList<User>>("QList<User>");
    qRegisterMetaType<PreKeys>("PreKeys");
}
