// Copyright (c) 2018 The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

import qbs

Product {
    type: "staticlibrary"
    name: "core"
    files: [
        "Utils.cpp",
        "Utils.hpp",
        "lib.cpp",
        "lib.h",
    ]
    Depends { name: "cpp" }
    Depends { name: "networking" }
    cpp.defines: ['CRUCIAL_DEFINE']

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [product.sourceDirectory]
    }

}
