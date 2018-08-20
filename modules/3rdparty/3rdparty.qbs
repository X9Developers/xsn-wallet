// Copyright (c) 2018 The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

import qbs

Module {
//    name: "vendor"
    Depends { name: "cpp" }

    property string includePath: path + "/include"

    cpp.includePaths: [
        includePath + "/gsl/include",
    ]
}
