import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

import "../Views"
import "../Popups"
import com.xsn.viewmodels 1.0

Page {
    id: root
    anchors.fill: parent
    property string currentAssetID: walletPage.currentAssetID
    background: Rectangle {
        color: "#090D1C"
    }

    Component {
        id: sendDialogComponent
        SendPopup {

        }
    }

    Component {
        id: receiveDialogComponent
        ReceivePopup {

        }
    }

    Component {
        id: transactionDatailsComponent
        TransactionsDetailsPopup
        {

        }
    }


    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width < windowWidthSmallMode ? menuWidthSmallMode : menuWidthLargeMode
            color: "#090D1C"

            WalletMenuListView {
                id: walletMenuListView
                onSendRequested: {
                    openSendDialog({});
                }
                onReceiveRequested: {
                    openReceiveDialog({});
                }
            }
        }

        StackLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            currentIndex: walletMenuListView.currentIndex

            PortfolioPage {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            WalletPage {
                id: walletPage
                Layout.fillHeight: true
                Layout.fillWidth: true
                windowWidth: root.parent.width
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignCenter

                Text {
                    anchors.centerIn: parent
                    text: "Coming soon"
                    color: "white"
                    font.pixelSize: 20
                }
            }

            Text {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Settings"
                color: "white"
            }
            //            TransactionPage {
            //                Layout.fillHeight: true
            //                Layout.fillWidth: true
            //            }
        }
    }

    function openDialog(component, params) {
        var dialog = component.createObject(root);
        dialog.open();
    }

    function openSendDialog(params) {
        openDialog(sendDialogComponent, params);
    }

    function openReceiveDialog(params) {
        openDialog(receiveDialogComponent, params);
    }

    function openTransactionDetailsDialog(params) {
        openDialog(transactionDatailsComponent, params)
    }
}
