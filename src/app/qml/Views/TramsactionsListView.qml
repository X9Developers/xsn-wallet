import QtQuick 2.0

Rectangle {
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
                   Text { text: '<b>Date:</b> ' + date }
                   Text { text: '<b>Type:</b> ' + type }
               }
           }
       }

       ListView {
           anchors.fill: parent
           model: lsitModel
           delegate: contactDelegate
           highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
           focus: true
       }
}
