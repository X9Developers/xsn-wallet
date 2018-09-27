import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0
import "../Components"

ActionDialog {
    id: root

    ColumnLayout{

        anchors.fill: root.container
        anchors.horizontalCenter: parent.horizontalCenter


        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }


        RowLayout {

            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true

            IconButton {
                id: iconBut
                Layout.preferredWidth: 30
                Layout.preferredHeight: 30
                source: "qrc:/images/Code.png"
                sourceSize: Qt.size(30, 30)
                hoverEnabled: true
            }

            ColumnLayout {

                //Layout.fillWidth: true
                Layout.maximumWidth: 350

                TextArea {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.fillWidth: true
                    font.bold: false;
                    font.pixelSize: 20;
                    color: "white"
                    placeholderText: "Send to Bitcoin address..."

                    cursorVisible: true
                    onTextChanged: if(text == "")
                                       lineAddress.color = "red"
                                   else
                                       lineAddress.color = "orange"
                }

                Rectangle{
                    id: lineAddress
                    Layout.alignment: Qt.AlignHCenter
                    Layout.fillWidth: true
                    Layout.preferredWidth: 350
                    height: 3
                    color: "orange"
                }
            }
        }


        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        ColumnLayout{

            Layout.alignment: Qt.AlignHCenter

            TextInput {
                id: btcCount
                text: "0"
                validator: IntValidator{bottom: 0; top: 99999999;}
                font.pixelSize: 20;
                color: "orange"
                onTextChanged: usdCount.text = parseInt(btcCount.text) * 6000
            }


            Rectangle{

                width:350
                height:3
                color: "orange"
            }

            TextInput {
                id: usdCount
                font.pixelSize: 20;
                text: "0"
                cursorVisible: false
            }
        }


        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        TransactionButton {
            anchors.horizontalCenter: parent.horizontalCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: 40
            baseColor: "orange"
            secondaryColor: "orange"
            radius: 25

            Text {
                anchors.centerIn: parent
                text: qsTr("SEND")
                color: "white"
                style: Text.StyledText
                styleColor: "black"
            }

            //            onClicked: sendCoins()
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }


        Rectangle
        {
            id: rec
            anchors.horizontalCenter: parent.horizontalCenter

            width: 350
            height: 100
            radius: 125
            color: "#1C1F24"


            RowLayout{

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                Layout.preferredHeight: 40

                Column{
                    Text { text: "Bitcoin Network Fee ( 0.078 KB )"; font.bold: true; font.pixelSize: 10; color: "grey" }
                    Text { text: "Remaining Balance"; font.bold: true; font.pixelSize: 10; color: "grey" }

                }

                Column{
                    Text { text: "0.0000078"; font.pixelSize: 10; color: "orange"}
                    Text { text: "0"; font.pixelSize: 10; color: "orange"}
                }

                Column{
                    Text { text: " BTC"; font.pixelSize: 10; color: "orange"}
                    Text { text: " BTC"; font.pixelSize: 10; color: "orange"}
                }

                Column{
                    Text { text: "$0.05"; font.pixelSize: 10; color: "white"}
                    Text { text: "$0.00"; font.pixelSize: 10; color: "white"}
                }
            }
        }
    }
}
