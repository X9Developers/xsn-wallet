import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Views"
import "../Components"
import "../Popups"

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

//    Component {
//        id: dialogComponent1
//        Dialog {
//            title: "Title"
//            standardButtons: Dialog.Ok | Dialog.Cancel

//            onAccepted: console.log("Ok clicked")
//            onRejected: console.log("Cancel clicked")
//        }
//    }



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
        color: assetsListView.currentItem.color

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
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 0

                WalletPageHeaderView {
                    Layout.preferredHeight: 270
                    Layout.fillWidth: true

                    coinMeasure: assetsListView.currentItem.name
                    labelColor: assetsListView.currentItem.color

                    onSendCoins: {
                        var dialog = sendDialogComponent.createObject(root)
                        dialog.width = 600;
                        dialog.height = 400;
                        dialog.x = root.width / 2 - dialog.width / 2;
                        dialog.y = root.height / 2 - dialog.height / 2;
                        dialog.open();
                    }

                    onReceiveCoins: {
                        var dialog = receiveDialogComponent.createObject(root)
                        dialog.width = 600;
                        dialog.height = 400;
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
