import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Views"
import "../Components"
import "../Popups"

import com.xsn.viewmodels 1.0
import com.xsn.models 1.0

Page {
    id: root
    property int windowWidth: 0
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

    Component {
        id: dialogComponent1
        Dialog {
            title: "Title"
            standardButtons: Dialog.Ok | Dialog.Cancel

            onAccepted: console.log("Ok clicked")
            onRejected: console.log("Cancel clicked")
        }
    }



    Component{
        id: sendDialogComponent
        ActionDialog {
        }
    }

    Component{
        id: receiveDialogComponent
        ReceivePopup {
        }
    }

    Rectangle {
        anchors.fill: parent
        color: currentAssetColor

        RowLayout {
            anchors.fill: parent
            spacing: 3

            Rectangle {
                Layout.fillHeight: true
                Layout.preferredWidth: windowWidth > 1180 ? 150 : 130
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

                    coinMeasure: currentAssetID
                    labelColor: currentAssetColor
                    buttonColor: assetsListView.currentItem.buttonColor
                    windowWidth: root.windowWidth


                    onSendCoins: {
                        var dialog = sendDialogComponent.createObject(root)
                        dialog.width = 500;
                        dialog.height = 300;
                        dialog.x = root.width / 2 - dialog.width / 2;
                        dialog.y = root.height / 2 - dialog.height / 2;
                        dialog.open();
                    }

                    onReceiveCoins: {
                        var dialog = receiveDialogComponent.createObject(root)
                        dialog.width = 500;
                        dialog.height = 300;
                        dialog.x = root.width / 2 - dialog.width / 2;
                        dialog.y = root.height / 2 - dialog.height / 2;
                        dialog.open();
                    }
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
