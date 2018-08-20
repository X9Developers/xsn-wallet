import QtQuick 2.0

ListView {
    id: root

    model: ListModel {
        ListElement { color: "lightblue"; name: "Dash" }
        ListElement { color: "darkblue"; name: "XSN" }
        ListElement { color: "orange"; name: "Bitcoin" }
    }

    highlight: Item {
        Rectangle {
            anchors.right: parent.right
            width: 5
            height: parent.height
            radius: 5
            //        x: currentItem.width - width
            //        y: currentItem.y
            color: currentItem.color
        }
    }

    highlightFollowsCurrentItem: true

    spacing: 10

    delegate: Item {
        height: 20
        width: parent.width

        property string color: model.color

        Text {
            anchors.fill: parent
            text: model.name

            font.pixelSize: 14
            color: parent.ListView.isCurrentItem ? parent.color : "grey"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.currentIndex = index;
            }
        }
    }
}
