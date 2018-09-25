import QtQuick 2.0

ListView {
    id: listView
    anchors.fill: parent

    model: ListModel {
        ListElement { baseColor: "#426DD3"; buttonColor: "#4927BB"; name: "Dash"; balance: "1.5"; } // color - blue
        ListElement { baseColor: "#18B8EE"; buttonColor: "#207EB4"; name: "XSN"; balance: "1.3"; } // color - light blue
        ListElement { baseColor: "#F8A502"; buttonColor: "#D9880A"; name: "Bitcoin"; icon: ""; balance: "2.7"; } //color - orange
    }

    highlight: Item {
        Rectangle {
            id: highlightItem
            anchors.right: parent.right
            width: 8
            height: parent.height
            radius: 5
            color: listView.currentItem.baseColor
        }
    }

    highlightFollowsCurrentItem: true

    delegate: Item {
        height: 45
        width: parent.width
        anchors.right: parent.right
        property string baseColor: model.baseColor
        property string name: model.name
        property string buttonColor: model.buttonColor

        Text {
            id: assetsName
            anchors.rightMargin: parent.width / 7
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            text: model.name

            font.pixelSize: 14
            color: parent.ListView.isCurrentItem ? parent.baseColor : mouseArea.containsMouse ? "white" : "grey"
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                listView.currentIndex = index;
            }
        }
    }
}
