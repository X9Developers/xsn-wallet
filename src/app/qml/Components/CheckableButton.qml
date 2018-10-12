import QtQuick 2.0
import QtQuick.Controls 2.3

Button {
    id: control
    checkable: true
    font.pixelSize: 12

    contentItem: XSNLabel {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.checked ? "#2C80FF" : "#6B78A6"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 45
        implicitHeight: 30
        color: control.checked ? "#0E1E3E" : "transparent"
        opacity: enabled ? 1 : 0.3
        radius: 5
    }
}
