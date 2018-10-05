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

        TransactionHeader {
            Layout.preferredWidth: parent.width * 0.08
            Layout.alignment: Qt.AlignCenter
            text: "Type";
        }

        TransactionHeader {
            Layout.preferredWidth: parent.width * 0.18
            text: "Date";
        }

        TransactionHeader {
            Layout.preferredWidth: parent.width * 0.16
            text: "Currency"
        }

        TransactionHeader {
            Layout.preferredWidth: parent.width * 0.22
            text: "Transaction ID"
        }

        Item {
            Layout.preferredWidth: parent.width * 0.18
            Layout.alignment: Qt.AlignRight

            TransactionHeader {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                text: "Amount";
            }
        }

        Item {
            Layout.preferredWidth: parent.width * 0.06
        }
    }
}
