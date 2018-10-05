import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

import "../Views"
import com.xsn.viewmodels 1.0

Page {
    id: root
    anchors.fill: parent
    property string currentAssetID: walletPage.currentAssetID
    background: Rectangle {
        color: "#090D1C"
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
            }
        }

        StackLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            currentIndex: walletMenuListView.currentIndex

            Text {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Portfolio"
            }

            Text {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Send"
                color: "white"
            }

            Text {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Receive"
                color: "white"
            }

            WalletPage {
                id: walletPage
                Layout.fillHeight: true
                Layout.fillWidth: true
                windowWidth: root.parent.width
            }

            TransactionPage {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Text {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Lightning"
                color: "white"
            }

            Text {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Exchange"
                color: "white"
            }

            Text {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Masternodes"
                color: "white"
            }

            Text {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "TPoS"
                color: "white"
            }

            Text {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Settings"
                color: "white"
            }
        }
    }
}
