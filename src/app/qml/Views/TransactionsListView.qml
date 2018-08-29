import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    color: "grey"

    Text {
        anchors.centerIn: parent
        text: "No Transactions"
        font.pixelSize: 12
    }



    ListModel {
        id: listModel
        ListElement {
            date: "28\nJUL"
            operationPic: "qrc:/images/received.jpg"
            type: "Received"
            transactionAmount: "+0.00435"

        }
        ListElement {
            date: " 15\nJUN"
            operationPic: "qrc:/images/images.png"
            type: "Sent"
            transactionAmount: "-0.00435"
        }
        ListElement {
            date: "7\nJUN"
            operationPic: "qrc:/images/received.jpg"
            type: "Received"
            transactionAmount: "+0.00435"
        }
    }

    //////////////
    Component {
        id: contactDelegate
        Rectangle{
            color: "grey"
            border.width: 1
            border.color: "black"
            width: parent.width
            height: 30

            RowLayout {
                width: parent.width
                height: parent.height
                //spacing:

                Text {
                    text: date
                }
                Image {
                    source: operationPic
                    sourceSize.width: 16
                    sourceSize.height: 16

                }
                Text {
                    text: type
                }
                Item {
                    Layout.fillWidth: true
                }
                Text {
                    text: transactionAmount
                }
            }
        }
    }

    ListView {
        anchors.fill: parent
        model: listModel
        delegate: contactDelegate
        focus: true
        spacing: 10
    }
}
