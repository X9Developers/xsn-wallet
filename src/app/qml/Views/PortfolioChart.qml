import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../Components"

ColumnLayout {

    RowLayout {
        Layout.fillWidth: true
        Layout.maximumHeight: 48
        XSNLabel {
            text: "Statistics"
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true

        }
        RowLayout {
            id: buttonsLayout
            Layout.maximumHeight: 32
            Repeater {
                model: ["Day", "Week", "Month", "Year"]
                delegate: CheckableButton {
                    text: modelData
                }
            }
        }
        ButtonGroup {
              buttons: buttonsLayout.children
        }
    }

    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true
        color: "#16192E"
        Text {
            text: "Chart"
            anchors.centerIn: parent
            color: "white"
        }

    }
}
