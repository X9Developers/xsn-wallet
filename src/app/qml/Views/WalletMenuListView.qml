import QtQuick 2.0
import QtQuick.Layouts 1.3

ListView {
    id: listView
    anchors.fill: parent

    model: ListModel {
        ListElement { name: "Portfolio"; image: "qrc:/images/images.png" }
        ListElement { name: "Wallet"; image:  "qrc:/images/received.jpg" }
        ListElement { name: "Exchange"; image:"qrc:/images/images.png" }
        ListElement { name: "Backup"; image: "qrc:/images/received.jpg" }
        ListElement { name: "Settings"; image : "qrc:/images/received.jpg"}
        ListElement { name: "Help"; image: "qrc:/images/received.jpg" }
    }

    delegate: Rectangle {
        height: 40
        width: parent.width
        color: ListView.isCurrentItem ? "#292E34" : "transparent"
        property string name: model.name

        RowLayout {
            anchors.leftMargin: parent.width / 7
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter

            Image {
                sourceSize.width: 16
                sourceSize.height: 16
                source: model.image
            }

            Text {
                text: model.name
                font.pixelSize: 14
                color: "white"
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                listView.currentIndex = index;
            }
        }
    }
}
