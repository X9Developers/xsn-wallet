import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Components"

Rectangle {
    id: backgroundRectangle
    color: "#292E34"

    property string coinMeasure: ""
    property string labelColor: ""

    ColumnLayout {
        anchors.fill: parent
        anchors.bottomMargin: 10
        anchors.topMargin: 20

        IconButton {
            id: iconBut
            source: hovered ? "qrc:/images/refresh.png" : coinMeasure !== "" ? "qrc:/images/%1.png".arg(coinMeasure): ""
            sourceSize: Qt.size(55, 55)
            anchors.horizontalCenter: parent.horizontalCenter
            hoverEnabled: true
        }

        Row {
            id: coins
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 5

            XSNLabel {
                id: coinsAmount
                text: "0"
                color: labelColor
                backgroundRectangleWidth: backgroundRectangle.width
                lineHeightMode: Text.FixedHeight
                height: 60
            }


            XSNLabel {
                text: coinMeasure
                anchors.bottom: coinsAmount.bottom
                color: labelColor
                font.pixelSize: coinsAmount.font.pixelSize * 0.4
                font.capitalization: Font.AllUppercase
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 5
            anchors.top: coins.bottom

            XSNLabel {
                text: qsTr("$")
                anchors.bottom: parent.bottom
                color: "grey"
                font.pixelSize: 22
            }

            XSNLabel {
                id: usdAmount
                text: "0.00" //qsTr("91.22")
                color: "white"
                anchors.bottom: parent.bottom
                font.pixelSize: 31
            }

            XSNLabel {
                text: "USD"
                anchors.bottom: parent.bottom
                color: "grey"
                font.pixelSize: 22
                font.capitalization: Font.AllUppercase
            }
        }

        RowLayout {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 25

            TransactionButton {
                Layout.preferredWidth: 235
                Layout.preferredHeight: 45
                color: labelColor
                radius: 25

                Text {
                    anchors.centerIn: parent
                    text: qsTr("SEND")
                    color: "white"
                    style: Text.StyledText
                    styleColor: "black"
                }
            }

            TransactionButton {
                Layout.preferredWidth: 235
                Layout.preferredHeight: 45
                color: labelColor
                radius: 25
                font.weight: Font.Light

                Text {
                    anchors.centerIn: parent
                    text: qsTr("RECEIVE")
                    color: "white"
                    style: Text.StyledText
                    styleColor: "black"
                }
            }
        }
    }
}

