import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Views"
import "../Components"

import com.xsn.viewmodels 1.0

Page {
    id: root
    property string currentAssetID: assetsListView.currentItem.name

    WalletAssetViewModel {
        id: walletViewModel
        Component.onCompleted: {
            initialize(ApplicationViewModel);
        }

        currentAssetID: root.currentAssetID
    }

    RowLayout {
        anchors.fill: parent

        WalletAssetsListView {
            id: assetsListView
            Layout.fillHeight: true
            Layout.maximumWidth: parent.width / 6
            Layout.minimumWidth: parent.width / 6
        }

        ColumnLayout {

            Layout.fillWidth: true
            Layout.fillHeight: true

            WalletPageHeaderView {
                Layout.fillHeight: true
                Layout.fillWidth: true

                coinMeasure: assetsListView.currentItem.name
                labelColor: assetsListView.currentItem.color
                //color: assetsListView.currentItem ? assetsListView.currentItem.color : ""
            }

            TransactionsListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: parent.height / 2
                transactionListModel: walletViewModel.transactionsListModel
            }
        }
    }
}
