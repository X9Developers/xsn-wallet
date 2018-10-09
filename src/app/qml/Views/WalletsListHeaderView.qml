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

        ListHeader {
            Layout.preferredWidth: parent.width * 0.2
            Layout.alignment: Qt.AlignVCenter
            text: "Currency";
        }

        Item {
            Layout.preferredWidth: parent.width * 0.3
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignRight & Qt.AlignVCenter

            ListHeader {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                text: "Balance"
            }
        }

        Item {
            Layout.preferredWidth: parent.width * 0.2
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignRight & Qt.AlignVCenter

            ListHeader {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                text: "Portfolio %"
            }
        }

        Item {
            Layout.preferredWidth: parent.width * 0.3
        }
    }
}
