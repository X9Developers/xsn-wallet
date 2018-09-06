import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Components"

Rectangle {
    id: backgroundRectangle
    color: "grey"

    property string coinMeasure: ""
    property string labelColor: ""

    ColumnLayout{

        anchors.fill: parent

        IconButton {
            id: iconBut
            source: hovered ? "qrc:/images/refresh.png" : "qrc:/images/BC_Logo_.png"
            sourceSize: Qt.size(55, 55)
            anchors.horizontalCenter: parent.horizontalCenter
            hoverEnabled: true
        }

        XSNLabel {
            text: qsTr("0.01347051 " + coinMeasure)
            anchors.horizontalCenter: parent.horizontalCenter
            color: labelColor // "Orange"
        }

        XSNLabel {
            text: qsTr("$91.22 USD")
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
        }

        Item {
            Layout.fillHeight: true
        }

        RowLayout{
            anchors.horizontalCenter: parent.horizontalCenter
            Layout.alignment: Layout.Bottom
            Layout.bottomMargin: 10

            TransactionButton{
                Layout.preferredWidth: 80
                color: labelColor
                radius: 20
                text: qsTr("Send")
            }

            TransactionButton{
                Layout.preferredWidth: 80
                color: labelColor
                radius: 20
                text: qsTr("Receive")
            }
        }
    }
}

