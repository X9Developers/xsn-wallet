// Copyright (c) 2018 The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

import qbs

CppApplication {
    Depends { name: "Qt.core" }
    Depends { name: "Qt.quick" }
    Depends { name: "core" }

    name: "XSNWallet"

    // Additional import path used to resolve QML modules in Qt Creator's code model
    property pathList qmlImportPaths: []

    cpp.cxxLanguageVersion: "c++11"

    cpp.defines: [
        // The following define makes your compiler emit warnings if you use
        // any feature of Qt which as been marked deprecated (the exact warnings
        // depend on your compiler). Please consult the documentation of the
        // deprecated API in order to know how to port your code away from it.
        "QT_DEPRECATED_WARNINGS",

        // You can also make your code fail to compile if you use deprecated APIs.
        // In order to do so, uncomment the following line.
        // You can also select to disable deprecated APIs only up to a certain version of Qt.
        //"QT_DISABLE_DEPRECATED_BEFORE=0x060000" // disables all the APIs deprecated before Qt 6.0.0
    ]

    files: [
        "QMLUtils.cpp",
        "QMLUtils.hpp",
        "assets/assets.qrc",
        "main.cpp",
        "qml/qml.qrc",
    ]

    cpp.includePaths: [product.sourceDirectory]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
    }
}
