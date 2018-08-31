import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

Rectangle {
    id: root
    property var transactionListModel: undefined
    color: "blue"
    //        height: 100
    //        width:  100

    ListModel {
        id: lsitModel
        ListElement {
            date: "28-05-18"
            type: "Received"
        }
        ListElement {
            date: "28-05-18"
            type: "Sent"
        }
        ListElement {
            date: "28-05-18"
            type: "Received"
        }
    }

    //////////////
    ColumnLayout {
        id: layout
        spacing: 0
        anchors.fill: parent.fill
        height: parent.height
        width: parent.width

        ListView {
            boundsBehavior: Flickable.StopAtBounds
            anchors.fill: parent
            model: transactionListModel
            //highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            //focus: true
            clip: true
            delegate: Item {
                width: 200; height: 80
                anchors.bottomMargin: 5
                Column {
                    Text { text: '<b>ID:</b> ' + id }
                    Text { text: isSend ?'<b>Type:</b> ' + "Send": '<b>Type:</b> ' + "Received"}
                    Text { text: '<b>Delta:</b> ' + delta }
                }
            }
        }
    }
}

