import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
import "../Components"

ActionDialog {
    id: root
    popUpText: "Receive"
    width: 503
    height: 399

    property string receivingAddress: ""

    ColumnLayout {
        anchors.fill: root.container
        anchors.margins: 20
        spacing: 3

        ListModel {
            id: coins
            ListElement { name: "Stakenet"; iconPath: "qrc:/images/Stakenet.png"; amount: "1000"; value: "XSN"}
            ListElement { name: "Dash"; iconPath: "qrc:/images/Stakenet.png"; amount: "100"; value: "DASH" }
            ListElement { name: "Bitcoin"; iconPath: "qrc:/images/Stakenet.png"; amount: "50"; value: "BTC" }
        }

        CoinsCombobox{
            model: coins
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            color: "transparent"
            border.color: "#2C3251"

            RowLayout
            {
                anchors.fill: parent
                anchors.margins: 15

                RoundedImage {
                    imageSource: "qrc:/images/alert@2x.png"
                }

                SecondaryLabel{
                    text: qsTr("Send only XSN to this address. Sending any \nother digital asset will result in permanent loss.")
                }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true

            SecondaryLabel{
                Layout.fillWidth: true
                text: qsTr("Receiving address")
            }

            Rectangle {

                Layout.fillWidth: true
                Layout.preferredHeight: 35

                color: "#090D1C"

                RowLayout {

                    anchors.fill: parent

                    TextField {
                        id: addressTxt
                        Layout.fillWidth: true
                        font.bold: false;
                        font.pixelSize: 14;
                        color: "#8C9CD4"
                        text: receivingAddress
                        background: Rectangle {
                            color: "transparent"
                        }
                        readOnly: true
                        cursorVisible: true

                        LinearGradient  {
                            anchors.fill: parent
                            source: addressTxt
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: "black" }
                                GradientStop { position: 0.5; color: "white" }
                                GradientStop { position: 1.0; color: "black" }
                            }
                        }
                    }

                    Button {

                        Layout.preferredWidth: 35
                        Layout.preferredHeight: 32

                        background: Rectangle {
                            color: "transparent"
                            radius: 1
                        }

                        Image {
                            id: image
                            anchors.centerIn: parent
                            sourceSize: Qt.size(32, 35)
                            source: "qrc:/images/qr@2x.png"
                        }
                    }

                    Button {
                        Layout.preferredWidth: 80
                        Layout.preferredHeight: 32

                        background: Rectangle {
                            color: "#2C3251"
                            radius: 4
                        }

                        XSNLabel {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "#FFFFFF"
                            font.pixelSize: 14
                            text: qsTr("Copy")
                        }

                    }
                }
            }
        }

        XSNLabel {
            Layout.fillWidth: true
            color: "#454C71"
            font.pixelSize: 14
            text: qsTr("•  Coins will be deposited after 20 network confirmations.")
        }

        XSNLabel {
            Layout.fillWidth: true
            color: "#454C71"
            font.pixelSize: 14
            text: qsTr("•  You can check the progress on transactions page.")
        }
    }
}

