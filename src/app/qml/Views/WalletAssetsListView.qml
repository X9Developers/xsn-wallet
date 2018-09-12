import QtQuick 2.0

ListView {
    id: listView
    anchors.fill: parent

    model: ListModel {
        ListElement { color: "lightblue"; name: "Dash"; balance: "1.5"; }
        ListElement { color: "darkblue"; name: "XSN"; balance: "1.3"; }
        ListElement { color: "orange"; name: "Bitcoin"; icon: ""; balance: "2.7"; }
    }

    highlight: Item {
        Rectangle {
            anchors.right: parent.right
            width: 5
            height: parent.height
            radius: 5
            color: listView.currentItem.color
        }
    }

    highlightFollowsCurrentItem: true

    delegate: Item {
        height: 35
        width: parent.width
        anchors.right: parent.right
        property string color: model.color
        property string name: model.name

        Text {
            anchors.rightMargin: parent.width / 7
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            text: model.name

            font.pixelSize: 14
            color: parent.ListView.isCurrentItem ? parent.color : "grey"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                listView.currentIndex = index;
            }
        }
    }
}
