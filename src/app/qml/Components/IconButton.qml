import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

Button {
    id: control
    property string source
    property alias sourceSize: image.sourceSize
    property color color: "transparent"
    property alias iconColor: colorOverlay.color
    property int radius: 0

    focusPolicy: Qt.NoFocus
    implicitWidth: image.sourceSize.width
    implicitHeight: image.sourceSize.height

    contentItem: Item {
        Image {
            id: image
            opacity: control.enabled ? 1 : 0.48
            anchors.centerIn: parent
            source: control.source
        }

        ColorOverlay {
            id: colorOverlay
            source: image
            anchors.fill: image
        }

        BrightnessContrast {
            visible: control.hovered
            source: colorOverlay
            anchors.fill: image
            brightness: 0.3
        }
    }

    background: Rectangle {
        color: control.color
        radius: control.radius
    }
}
