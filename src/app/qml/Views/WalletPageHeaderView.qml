import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Components"

Item {
    id: root

    signal sendCoins()
    signal receiveCoins()

    property string coinMeasure: ""
    property string coinSymbol : ""
    property string labelColor: ""
    property int windowWidth: 0
    property string buttonColor: ""

    ColumnLayout {
        anchors.fill: parent
        anchors.bottomMargin: 10
        anchors.topMargin: 20
        spacing: 10

        IconButton {
            id: iconBut
            source: hovered ? "qrc:/images/refresh.png" : coinMeasure !== "" ? "qrc:/images/%1.png".arg(coinMeasure): ""
            sourceSize: Qt.size(75, 75)
            Layout.alignment: Qt.AlignHCenter
            hoverEnabled: true
        }

        Row {
            id: coins
            Layout.alignment: Qt.AlignHCenter
            spacing: 5

            XSNLabel {
                id: coinsAmount
                text: "732.12"
                font.pixelSize: 60// windowWidth > 1180 ? (root.parent.width > 1250 ? 100 : 75)
                // : 60
            }

            XSNLabel {
                text: coinSymbol
                anchors.top: coinsAmount.top
                font.pixelSize: coinsAmount.font.pixelSize * 0.5
                font.capitalization: Font.AllUppercase
            }
        }

        Row {
            id: usd
//            anchors.top: coins.bottom
            Layout.alignment: Qt.AlignHCenter
            spacing: 5

            XSNLabel {
                text: qsTr("$")
                anchors.bottom: parent.bottom
                color: "#7F8DC1"
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
                color: "#7F8DC1"
                font.pixelSize: 22
                font.capitalization: Font.AllUppercase
            }
        }

        RowLayout {
            anchors.top: usdAmount.bottom
            anchors.topMargin: 15
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 25

            ActionButton {
                Layout.preferredWidth: 130
                Layout.preferredHeight: 40
                buttonText: qsTr("Send")
                source: "qrc:/images/icons-1 stroke-16px-withdraw.png"
                onClicked: sendCoins()
            }

            ActionButton {
                Layout.preferredWidth: 130
                Layout.preferredHeight: 40
                font.weight: Font.Light
                buttonText: qsTr("Receive")
                source: "qrc:/images/icons-1 stroke-16px-deposit.png"
                onClicked: receiveCoins();
            }
        }

    }
}
