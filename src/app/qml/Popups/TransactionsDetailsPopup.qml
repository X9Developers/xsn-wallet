import QtQuick 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
import "../Components"

ActionDialog {
    id: root
    popUpText: "Send"
    width: 503
    height: 464

    ColumnLayout {
        anchors.fill: root.container
        anchors.margins: 20
        spacing: 18

        ComboBox {
            Layout.fillWidth: true
            model: [ "Stakenet", "Dash", "Bitcoin" ]
        }

        ColumnLayout {
            Layout.fillWidth: true

            SecondaryLabel {
                Layout.fillWidth: true
                text: qsTr("Send funds to")
            }

            Rectangle {
                color: "#090D1C"
                Layout.fillWidth: true
                Layout.preferredHeight: 35

                RowLayout {

                    Layout.fillWidth: true
                    anchors.fill: parent
                    spacing: 10

                    Image {
                        Layout.leftMargin: 10
                        sourceSize: Qt.size(20, 20)
                        source: "qrc:/images/icons-1 stroke-16px-withdraw.png"
                    }


                    TextArea {
                        Layout.fillWidth: true
                        font.bold: false;
                        font.pixelSize: 14;
                        color: "#8C9CD4"
                        placeholderText: "Enter the XSN address"

                        background: Rectangle {
                            color: "transparent"
                        }

                        cursorVisible: true
                    }
                }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true

            RowLayout{

                Layout.fillWidth: true

                SecondaryLabel{
                    Layout.fillWidth: true
                    font.pixelSize: 12
                    text: qsTr("Amount")
                }

                Item {
                    Layout.fillWidth: true
                }

                Item {
                    Layout.fillWidth: true
                }

                XSNLabel {
                    color: "#454C71"
                    font.pixelSize: 12
                    text: qsTr("Available")
                }


                SecondaryLabel{
                    font.pixelSize: 12
                    text: qsTr("2 535.00 XSN")
                }

                SecondaryLabel{
                    font.pixelSize: 12
                    text: qsTr("$ 721.35")
                }

            }

            Rectangle{

                color: "#090D1C"
                Layout.fillWidth: true
                Layout.preferredHeight: 35

                RowLayout{

                    anchors.fill: parent
                    spacing: 10

                    Image {
                        Layout.leftMargin: 10
                        sourceSize: Qt.size(20, 20)
                        source: "qrc:/images/coins@2x.png"
                    }

                    TextArea {
                        Layout.preferredWidth: 120
                        font.bold: false;
                        font.pixelSize: 14;
                        color: "#8C9CD4"
                        placeholderText: "XSN "

                        background: Rectangle {
                            color: "transparent"
                        }

                        cursorVisible: true
                    }

                    Image {
                        Layout.leftMargin: 10
                        sourceSize: Qt.size(20, 20)
                        source: "qrc:/images/usd@2x.png"
                    }

                    SecondaryLabel{
                        Layout.fillWidth: true
                        text: qsTr("USD")
                    }

                    Button {

                        Layout.fillWidth: true
                        Layout.preferredHeight: 32

                        background: Rectangle {
                            color: "#8C9CD4"
                            radius: 2
                        }

                        XSNLabel{
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "#FFFFFF"
                            font.pixelSize: 12
                            text: qsTr("Max amount")
                        }

                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 60

            SecondaryLabel {
                text: qsTr("Network fee: ")
            }

            XSNLabel {
                color: "#FFFFFF"
                font.pixelSize: 14
                text: qsTr("15 XSN")
            }

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            SecondaryLabel {
                text: qsTr("Remaining balance: ")
            }

            XSNLabel {
                color: "#FFFFFF"
                font.pixelSize: 14
                text: qsTr("319.26853 XSN")
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        RowLayout {
            Layout.fillWidth: true

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            SecondaryButton {
                text: "Close"
            }

            PrimaryButton {
                text: "View in explorer"
                Layout.alignment: Layout.Right
            }
        }
    }
}

