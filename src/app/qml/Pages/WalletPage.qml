import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Views"
import "../Components"

import com.xsn.viewmodels 1.0
import com.xsn.models 1.0

Page {
    id: root
    property string currentAssetID: assetsListView.currentItem ? assetsListView.currentItem.name : ""
    property string currentAssetColor: assetsListView.currentItem ? assetsListView.currentItem.color : ""
    property string currentAssetSymbol: assetsListView.currentItem ? assetsListView.currentItem.symbol : ""

    WalletAssetViewModel {
        id: walletViewModel
        Component.onCompleted: {
            initialize(ApplicationViewModel);
        }
        currentAssetID: root.currentAssetID
    }

    Rectangle {
        anchors.fill: parent
        color: currentAssetColor

        RowLayout {
            anchors.fill: parent
            spacing: 3

            Rectangle {
                Layout.fillHeight: true
                Layout.maximumWidth: 150
                Layout.minimumWidth: 150
                color: "#292E34"

                WalletAssetsListView {
                    id: assetsListView
                    anchors.fill: parent
                    model: WalletAssetsListModel {
                        Component.onCompleted: initialize(ApplicationViewModel)

                        onModelReset: {
                            assetsListView.currentIndex = 0;
                        }
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 0

                WalletPageHeaderView {
                    Layout.preferredHeight: 270
                    Layout.fillWidth: true

                    coinMeasure: currentAssetSymbol
                    labelColor: currentAssetColor
                    //color: assetsListView.currentItem ? assetsListView.currentItem.color : ""
                }

                TransactionsListView {
                    assetName: currentAssetID
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    transactionListModel: walletViewModel.transactionsListModel
                }
            }
        }
    }
}
