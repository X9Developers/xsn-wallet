import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0


Button {
    id: actionButton

    property color baseColor: "transparent"
    property color secondaryColor: "transparent"
    property int radius: 0

    background: Rectangle {
        color: actionButton.baseColor
        radius: actionButton.radius
        gradient: Gradient {
            GradientStop { position: 0.0; color: baseColor }
            GradientStop { position: 1.0; color: secondaryColor }
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: actionButton.clicked()
            onEntered:  {
                actionButton.scale = scale * 1.05
            }
            onExited: {
                actionButton.scale = scale
            }
        }
    }
}
