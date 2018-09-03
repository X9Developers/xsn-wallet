import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

import "Pages"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    RowLayout {
        anchors.fill: parent
        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"

            WalletPage {
                anchors.fill: parent
            }
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumWidth: parent.width / 3
            color: "white"

            EmulatorPage {
                anchors.fill: parent
            }
        }
    }
}
