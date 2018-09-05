// Copyright (c) 2018 The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

import qbs

Module {
//    name: "vendor"
    Depends { name: "cpp" }

    property string includePath: path
    property string libFolder: includePath + "/lib/"
    property var libs: [
        "system",
        "thread",
        "program_options",
        "regex"
    ]

    cpp.includePaths: [
        includePath + "/include",
    ]

    cpp.staticLibraries: libs.map(function(libName) { return libFolder + "libboost_" + libName + ".a" })
}
