import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import "../Components"

ListView {
    id: listView

    model: ["Assets", "Localization", "Skins"]
    property int actualIndex: 0

    anchors.leftMargin: 10
    anchors.rightMargin: 10
    anchors.fill: parent
    clip: true

    highlight: Item {
        Rectangle {
            id: highlightItem
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            width: 100
            height: 3
            color: "grey"
        }
    }

    orientation: ListView.Horizontal
    highlightFollowsCurrentItem: true
    spacing: 15

    delegate: Item {
        id: asset
        height: parent.height
        width: 110

            XSNLabel {
                anchors.centerIn: parent
                id: assetsName
                text: modelData
                font.pixelSize: 15
                color: asset.ListView.isCurrentItem ? "grey" : mouseArea.containsMouse ? "white" : "#6B78A6"
            }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                listView.actualIndex = index;
                listView.currentIndex = index;
            }
        }
    }
}
