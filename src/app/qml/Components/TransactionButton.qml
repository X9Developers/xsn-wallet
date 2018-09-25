import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0


Button {
    id: actionButton

    property color color: "transparent"
    property int radius: 0

    background: Rectangle {
        color: actionButton.color
        radius: actionButton.radius

        //        gradient: Gradient {
        //                GradientStop { position: 0.0; color: "#426DD3" }
        //                GradientStop { position: 1.0; color: "#4927BB" }
        //            }

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
