// Copyright (c) 2018 The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

import qbs

Module {
//    name: "vendor"
    Depends { name: "cpp" }
    Depends { name: "boost" }

    property string includePath: path
    property string libFolder: includePath + "/lib/"

    cpp.includePaths: [
        includePath + "/include/bitcoin",
        includePath + "/include",
    ]

    cpp.staticLibraries: [
        libFolder + "libbitcoin.a",
        libFolder + "libsecp256k1.a"
    ]

    cpp.dynamicLibraries: [
        "gmp"
    ]
}
