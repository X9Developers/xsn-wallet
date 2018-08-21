// Copyright (c) 2018 The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

import qbs

Product {
    type: "staticlibrary"
    name: "core"
    files: [
        "Models/WalletTransactionsListModel.cpp",
        "Models/WalletTransactionsListModel.hpp",
        "Utils.cpp",
        "Utils.hpp",
        "ViewModels/WalletAssetViewModel.cpp",
        "ViewModels/WalletAssetViewModel.hpp",
    ]
    Depends { name: "cpp" }
    Depends { name: "Qt.core" }
//    Depends { name: "networking" }
    cpp.defines: ['CRUCIAL_DEFINE']
    cpp.includePaths: [product.sourceDirectory]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [product.sourceDirectory]
    }

}
