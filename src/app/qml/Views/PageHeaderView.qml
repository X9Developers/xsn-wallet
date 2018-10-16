import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Components"

ColumnLayout {
    id: root
    signal sendCoins()
    signal receiveCoins()

    property string mainHeader: ""
    property string coinSymbol : ""
    property int windowWidth: 0
    property bool buttonsVisible: false

    RowLayout {
        Layout.fillWidth: true
        Layout.preferredHeight: 30
        Layout.topMargin: 10
        Layout.bottomMargin: 10
        Layout.rightMargin: 10

        XSNLabel {
            text: mainHeader
        }

        Item {
            Layout.fillWidth: true
        }

        Row {
            visible: false
            id: buttonRow
            height: parent.height
            spacing: 10

            Repeater {
                model: ["Day", "Week", "Month", "Year"]
                delegate: CheckableButton {
                    text: modelData
                }
            }
        }

        ButtonGroup {
            buttons: buttonRow.children
        }
    }

    Rectangle {
        Layout.preferredHeight: 100 //360
        Layout.fillWidth: true
        color: "#16192E"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20

            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: 60

                ColumnLayout {
                    Layout.maximumWidth: root.width / 3
                    Layout.fillHeight: true

                    Row {
                        Layout.fillWidth: true
                        spacing: 5

                        XSNLabel {
                            id: coinsAmount
                            text: "73 612.12"
                        }

                        XSNLabel {
                            text: coinSymbol
                            anchors.top: coinsAmount.top
                            font.pixelSize: coinsAmount.font.pixelSize * 0.5
                            font.capitalization: Font.AllUppercase
                        }
                    }

                    XSNLabel {
                        text: "$ %1" .arg("18 673.72")
                        color: "#6E7BAA"
                        font.pixelSize: 12
                    }

                }

                ColumnLayout {
                    Layout.maximumWidth: root.width / 3
                    Layout.fillHeight: true

                    Row {
                        id: usd
                        Layout.fillWidth: true
                        spacing : 5

                        XSNLabel {
                            id: usdAmount
                            text: "+ 624.73"
                        }

                        XSNLabel {
                            text: "USD"
                            anchors.top: usdAmount.top
                            font.pixelSize: coinsAmount.font.pixelSize * 0.5
                            font.capitalization: Font.AllUppercase
                        }
                    }

                    XSNLabel {
                        text: "+ %1%" .arg("5.09")
                        color: "#1DB182"
                        font.pixelSize: 12
                    }
                }

                RowLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                    visible: buttonsVisible
                    spacing: 10

                    ActionButton {
                        Layout.preferredWidth: 110
                        Layout.preferredHeight: 40
                        buttonText: qsTr("Send")
                        source: "qrc:/images/icons-1 stroke-16px-withdraw.png"

                        onClicked: sendCoins()
                    }

                    ActionButton {
                        Layout.preferredWidth: 110
                        Layout.preferredHeight: 40
                        font.weight: Font.Light
                        buttonText: qsTr("Receive")
                        source: "qrc:/images/icons-1 stroke-16px-deposit.png"

                        onClicked: receiveCoins();
                    }
                }
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                visible: false

                XSNLabel {
                    text: "Chart"
                    anchors.centerIn: parent
                    color: "white"
                }
            }
        }
    }
}
