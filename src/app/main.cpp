// Copyright (c) 2018 The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QMLUtils.hpp>
#include <Utils/Common.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QMLUtils::RegisterQMLTypes();
    RegisterCommonQtTypes();

    QQmlApplicationEngine engine;
    QMLUtils::setContextProperties(engine.rootContext());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
