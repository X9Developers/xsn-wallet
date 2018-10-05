import QtQuick 2.0
import QtQuick.Controls 2.3

Button {
    id: control
    checkable: true

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.checked ? "#2C80FF" : "#8C9CD4"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 69
        implicitHeight: 32
        color: control.checked ? "#2559A7" : "transparent"
        opacity: enabled ? 1 : 0.3
        radius: 2
    }
}
