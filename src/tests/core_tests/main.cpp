// Copyright (c) %YEAR The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "tst_coretests.hpp"
#include "tst_keystorage.hpp"
#include "tst_portalhttpclient.hpp"

#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    QCoreApplication app(argc, argv);
    QTimer::singleShot(0, []{
        QCoreApplication::exit(RUN_ALL_TESTS());
    });
    return app.exec();
}
