import QtQuick 2.0

Rectangle {
    property var transactionListModel: undefined
    color: "blue"
    //        height: 100
    //        width:  100


    Text {
        anchors.centerIn: parent
        text: "No Transactions"
        font.pixelSize: 12
    }



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
    Component {
           id: contactDelegate
           Item {
               width: 200; height:40
               Column {
                   Text { text: '<b>ID:</b> ' + id }
                   Text { text: '<b>Delta:</b> ' + delta }
               }
           }
       }

       ListView {
           anchors.fill: parent
           model: transactionListModel
           delegate: contactDelegate
           highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
           focus: true
       }
}
