import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../Components"

ColumnLayout {

    RowLayout {
        Layout.fillWidth: true
        Layout.maximumHeight: 48
        XSNLabel {
            text: "Wallets"
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        SecondaryLabel {
            text: qsTr("Sort by")
        }
    }

    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true
        color: "#16192E"

        WalletsListView {
            anchors.fill: parent
        }

    }
}
