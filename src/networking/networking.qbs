// Copyright (c) 2018 The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

import qbs

Product {
    type: "staticlibrary"
    name: "networking"
    files: [
        "AbstractMailHttpClient.*",
//        "*.cpp",
//        "*.hpp"
    ]
    Depends { name: "Qt.core" }
    Depends { name: "cpp" }
    Depends { name: "3rdparty" }
    cpp.defines: ['CRUCIAL_DEFINE']

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [product.sourceDirectory]
    }
}
