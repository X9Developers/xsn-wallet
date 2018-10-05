// Copyright (c) 2018 The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

import qbs

Product {
    type: "staticlibrary"
    name: "core"
    files: [
        "Data/CoinAsset.cpp",
        "Data/CoinAsset.hpp",
        "Data/TransactionEntry.cpp",
        "Data/TransactionEntry.hpp",
        "Data/WalletAssetsModel.cpp",
        "Data/WalletAssetsModel.hpp",
        "Models/AssetTransactionsDataSource.cpp",
        "Models/AssetTransactionsDataSource.hpp",
        "Models/EmulatorWalletDataSource.cpp",
        "Models/EmulatorWalletDataSource.hpp",
        "Models/TransactionsDataSource.cpp",
        "Models/TransactionsDataSource.hpp",
        "Models/WalletAssetsListModel.cpp",
        "Models/WalletAssetsListModel.hpp",
        "Models/WalletDataSource.cpp",
        "Models/WalletDataSource.hpp",
        "Models/WalletTransactionsListModel.cpp",
        "Models/WalletTransactionsListModel.hpp",
        "Utils/*",
        "Storage/*",
        "ViewModels/ApplicationViewModel.cpp",
        "ViewModels/ApplicationViewModel.hpp",
        "ViewModels/EmulatorViewModel.cpp",
        "ViewModels/EmulatorViewModel.hpp",
        "ViewModels/WalletAssetViewModel.cpp",
        "ViewModels/WalletAssetViewModel.hpp",
    ]
    Depends { name: "cpp" }
    Depends { name: "Qt.core" }
    Depends { name: "gsl" }
    Depends { name: "bitcoin" }
    Depends { name: "boost"}
    cpp.defines: ['CRUCIAL_DEFINE']
    cpp.includePaths: [product.sourceDirectory]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [product.sourceDirectory]
    }
}
