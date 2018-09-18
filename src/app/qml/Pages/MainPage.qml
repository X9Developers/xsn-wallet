import QtQuick 2.0
import QtQuick.Layouts 1.3

import "../Views"

RowLayout {
    anchors.fill: parent
    spacing: 0
    property string currentAssetID: walletPage.currentAssetID

    Rectangle {
        visible: false
        Layout.fillHeight: true
        Layout.maximumWidth: parent.width / 7
        Layout.minimumWidth: parent.width / 7
        color: "#3F444A"

        WalletMenuListView {
            id: walletMenuListView
        }
    }

    StackLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true
//        currentIndex: walletMenuListView.currentIndex
        currentIndex: 1

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Portfolio"
        }

        WalletPage {
            id: walletPage
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Exchange"
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Backup"
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Settings"
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Help"
        }
    }

}
