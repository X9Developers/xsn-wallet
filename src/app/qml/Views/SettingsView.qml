import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

import "../Components"

StackLayout {
    anchors.leftMargin: 10

    Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignCenter

        XSNLabel {
            anchors.centerIn: parent
            text: "Coming soon"
            color: "white"
            font.pixelSize: 20
        }
    }

    LocalizationView {
        Layout.fillHeight: true
        Layout.fillWidth: true
    }

    Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignCenter

        XSNLabel {
            anchors.centerIn: parent
            text: "Coming soon"
            color: "white"
            font.pixelSize: 20
        }
    }
}
