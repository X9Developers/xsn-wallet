// Copyright (c) 2018 The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

import qbs

Product {
    type: "staticlibrary"
    name: "bitcoin"
    files: [
        "*",
        "*/*",
        "*/*/*"
    ]
    Depends { name: "cpp" }
    Depends { name: "libbitcoin" }
    cpp.defines: ['CRUCIAL_DEFINE']
    cpp.cxxLanguageVersion: "c++11"
    cpp.includePaths: [product.sourceDirectory]
    cpp.staticLibraries: ["ssl", "crypto"]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [product.sourceDirectory]
    }

}
