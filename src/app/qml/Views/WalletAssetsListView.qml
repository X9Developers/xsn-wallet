import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import "../Components"

ListView {
    id: listView

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
            color: listView.currentItem.color
        }
    }

    orientation: ListView.Horizontal
    highlightFollowsCurrentItem: true
    spacing: 15

    delegate: Item {
        id: asset
        height: parent.height
        width: 110

        property string color: model.color
        property int id: model.id
        property string name: model.name
        property string symbol: model.symbol
        property var balance: model.balance
        property var usdBalance: model.usdBalance

        RowLayout {
            spacing: 7
            anchors.centerIn: parent

            Image {
                sourceSize: Qt.size(25, 25)
                source: "qrc:/images/%1.png" .arg(asset.name)
            }

            XSNLabel {
                id: assetsName
                text: model.name
                font.pixelSize: 15
                color: asset.ListView.isCurrentItem ? asset.color : mouseArea.containsMouse ? "white" : "#6B78A6"
            }
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
