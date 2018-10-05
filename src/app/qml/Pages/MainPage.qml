import QtQuick 2.0
import QtQuick.Layouts 1.3

import "../Views"

RowLayout {
    id: root
    anchors.fill: parent
    spacing: 0
    property string currentAssetID: walletPage.currentAssetID

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

        PortfolioPage {
            Layout.fillHeight: true
            Layout.fillWidth: true
            windowWidth: root.parent.width
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Send"
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Receive"
        }

        WalletPage {
            id: walletPage
            Layout.fillHeight: true
            Layout.fillWidth: true
            windowWidth: root.parent.width
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Transactions"
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Lightning"
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Exchange"
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Masternodes"
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "TPoS"
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Settings"
        }
    }
}
