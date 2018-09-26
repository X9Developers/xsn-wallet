import QtQuick 2.0
import QtGraphicalEffects 1.0

Image {
    id: img

    property string imageSource: ""
    property bool rounded: true
    property bool adapt: true
    width: 50
    height: 50

    sourceSize.width: 50
    sourceSize.height: 50
    source: imageSource

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
//        onClicked: actionButton.clicked()
        onEntered:  {
            img.scale = scale * 1.1
        }
        onExited: {
            img.scale = scale
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: "orange"
        border.width: 1
        radius: parent.width / 2
    }

//    layer.enabled: rounded
//    layer.effect: OpacityMask {
//        maskSource: Item {
//            width: img.width
//            height: img.height
//            Rectangle {
//                anchors.centerIn: parent
//                width: img.adapt ? img.width : Math.min(img.width, img.height)
//                height: img.adapt ? img.height : width
//                radius: Math.min(width, height)
//            }
//        }
//    }
}
