import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

Item {
    id: control
    property string source: ""
    property color color: "transparent"

    implicitWidth: image.sourceSize.width
    implicitHeight: image.sourceSize.height

    Image {
        id: image
        anchors.centerIn: parent
        sourceSize: Qt.size(25, 25)
        source: parent.source
    }

    ColorOverlay {
        anchors.fill: image
        source: image
        color: parent.color
    }
}
