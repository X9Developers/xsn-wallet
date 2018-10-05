// Copyright (c) 2018 The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

import qbs
import qbs.Utilities

Project {
    references: [
        "src/app/app.qbs",
        "src/core/core.qbs",
        "src/bitcoin/bitcoin.qbs"
//        "src/networking/networking.qbs",
    ]


    SubProject {
        filePath: "src/tests/tests.qbs"
    }

    AutotestRunner {
        name: "run_autotests"
    }
}
