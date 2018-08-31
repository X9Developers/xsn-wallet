import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Views"
import "../Components"

import com.xsn.viewmodels 1.0

Page {

    WalletAssetViewModel {
        id: walletViewModel
        applicationViewModel: ApplicationViewModel
    }

    EmulatorView {
        id: emularorView
        anchors.fill: parent
        onAddTransaction: walletViewModel.addTransaction();
        transactionListModel: walletViewModel.transactionsListModel
    }
}
