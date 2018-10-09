import QtQuick 2.0
import QtQuick.Layouts 1.3

import "../Components"

Rectangle {
    color: "#20233D"
    radius: 4

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        spacing: width * 0.02

        ListHeader {
            Layout.preferredWidth: parent.width * 0.08
            Layout.alignment: Qt.AlignCenter
            text: "Type";
        }

        RowLayout {
            Layout.preferredWidth: parent.width * 0.18
            Layout.fillHeight: true
            spacing: 5

            ListHeader {
                id: date
                text: "Date"
            }

            ColorOverlayImage {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignLeft
                imageSource: "qrc:/images/icons-1 stroke-16px-filter.png"
                imageSize: 15
                color: "#7F8DC1"
            }
        }

        ListHeader {
            Layout.alignment: Qt.AlignLeft
            Layout.preferredWidth: parent.width * 0.16
            text: "Currency"
        }

        ListHeader {
            Layout.preferredWidth: parent.width * 0.23
            text: "Transaction ID"
        }

        Item {
            Layout.preferredWidth: parent.width * 0.18
            Layout.alignment: Qt.AlignRight

            ListHeader {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                text: "Amount"
            }
        }

        Item {
            Layout.preferredWidth: parent.width * 0.06
        }
    }
}
