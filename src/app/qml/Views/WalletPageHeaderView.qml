import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Components"

ColumnLayout {
    id: root
    signal sendCoins()
    signal receiveCoins()

    property string coinMeasure: ""
    property string coinSymbol : ""
    property int windowWidth: 0

    RowLayout {
        Layout.fillWidth: true
        Layout.preferredHeight: 30
        Layout.topMargin: 10
        Layout.bottomMargin: 10
        Layout.rightMargin: 10

        XSNLabel {
            Layout.alignment: Qt.AlignVCenter
            text: coinMeasure
        }

        Item {
            Layout.fillWidth: true
        }

        ListView {
            id: listView
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: contentWidth
            Layout.alignment: Qt.AlignVCenter
            anchors.right: parent.right

            boundsBehavior: Flickable.StopAtBounds
            orientation: ListView.Horizontal

            spacing: 10

            model: ["Day", "Week", "Month", "Year"]

            highlight: Item {
                Rectangle {
                    id: highlightItem
                    color: "#0E1E3E"
                    height: parent.height
                    width: 45
                    radius: 5
                }
            }

            highlightFollowsCurrentItem: true

            delegate: Item {
                width: 45
                height: parent.height

                Text {
                    id: text
                    anchors.centerIn: parent
                    text: modelData
                    color: listView.currentIndex === index ? "#2C80FF" : "white"
                    font.pixelSize: 11
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        listView.currentIndex = index;
                    }
                }
            }
        }
    }

    Rectangle {
        Layout.preferredHeight: 360
        Layout.fillWidth: true
        color: "#16192E"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20

            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: 60
                spacing: 25

                ColumnLayout {
                    Layout.fillHeight: true
                    Layout.preferredWidth: 50

                    Row {
                        Layout.fillWidth: true
                        Layout.preferredWidth: 50
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

                    Text {
                        text: "$ %1" .arg("18 673.72")
                        color: "#6E7BAA"
                        font.pixelSize: 12
                    }

                }

                ColumnLayout {
                    Layout.preferredWidth: 50
                    Layout.fillHeight: true

                    Row {
                        id: usd
                        Layout.fillWidth: true
                        Layout.preferredWidth: 50
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

                    Text {
                        text: "+ %1%" .arg("5.09")
                        color: "#1DB182"
                        font.pixelSize: 12
                    }
                }

                Item {
                    Layout.fillWidth: true
                }

                RowLayout {
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent / 3
                    Layout.alignment: Qt.AlignVCenter
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

                Text {
                    text: "Chart"
                    anchors.centerIn: parent
                    color: "white"
                }
            }
        }
    }
}
