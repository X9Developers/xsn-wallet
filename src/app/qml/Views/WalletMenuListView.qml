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
        ListElement {name: "Settings"; image : "qrc:/images/received.jpg"}
        ListElement { name: "Help"; image: "qrc:/images/received.jpg" }
    }

    highlight: Item {
        Rectangle {
            anchors.right: parent.right
            width: 5
            height: parent.height
            radius: 5
            color: "darkgrey"
            clip: true
        }
    }

    highlightFollowsCurrentItem: true

    delegate: Rectangle {
        height: 20
        width: parent.width
        color: ListView.isCurrentItem ? "darkgrey" : "grey"

        property string name: model.name

        RowLayout {
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
