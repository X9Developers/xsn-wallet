import QtQuick 2.0
import QtQuick.Layouts 1.3

import "../Views"

RowLayout {

    Rectangle {
        Layout.fillHeight: true
        Layout.maximumWidth: parent.width / 7
        Layout.minimumWidth: parent.width / 7

        WalletMenuListView {
            id: walletMenuListView
        }
    }

    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true
        color: "transparent"

        WalletPage {
            id: walletPage
            anchors.fill: parent
            visible: walletMenuListView.currentItem.name === "Wallet"
        }
    }

    Rectangle {
        Layout.fillHeight: true
        Layout.maximumWidth: parent.width / 6
        Layout.minimumWidth: parent.width / 6
        color: "white"
        visible: walletMenuListView.currentItem.name === "Wallet"

        EmulatorPage {
            id: emulatorPage
            modelName: walletPage.currentAssetID
            anchors.fill: parent
        }
    }
}
