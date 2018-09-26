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
    property int currentAssetID: assetsListView.currentItem ? assetsListView.currentItem.id : 0
    property string currentAssetName: assetsListView.currentItem ? assetsListView.currentItem.name : ""
    property string currentAssetColor: assetsListView.currentItem ? assetsListView.currentItem.color : ""
    property string currentAssetSymbol: assetsListView.currentItem ? assetsListView.currentItem.symbol : ""
    property string currentButtonColor: assetsListView.currentItem ? assetsListView.currentItem.buttonColor : ""

    WalletAssetViewModel {
        id: walletViewModel
        Component.onCompleted: {
            initialize(ApplicationViewModel);
        }
        currentAssetID: root.currentAssetID
    }

    Component{
        id: sendDialogComponent
        SendPopup {

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
                    Layout.preferredHeight: windowWidth > 1180 ? (width > 1250 ? 350 : 300)
                                                               : 270
                    Layout.fillWidth: true

                    coinMeasure: currentAssetName
                    labelColor: currentAssetColor
                    buttonColor: currentButtonColor
                    coinSymbol: currentAssetSymbol
                    windowWidth: root.windowWidth


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
                }

                TransactionsListView {
                    assetName: currentAssetName
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    transactionListModel: walletViewModel.transactionsListModel
                }
            }
        }
    }
}
