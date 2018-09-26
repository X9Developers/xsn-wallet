import QtQuick 2.0

ListView {
    id: listView
    anchors.fill: parent

    highlight: Item {
        Rectangle {
            id: highlightItem
            anchors.right: parent.right
            width: 8
            height: parent.height
            radius: 3
            color: listView.currentItem.color
        }
    }

    highlightFollowsCurrentItem: true

    delegate: Item {
        height: 50
        width: parent.width
        anchors.right: parent.right
        property string color: model.color
        property int id: model.id
        property string name: model.name
        property string buttonColor: model.buttonColor
        property string symbol: model.symbol

        Text {
            id: assetsName
            anchors.rightMargin: parent.width / 7
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            text: model.name

            font.pixelSize: 15
            color: parent.ListView.isCurrentItem ? parent.color : mouseArea.containsMouse ? "white" : "grey"
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
