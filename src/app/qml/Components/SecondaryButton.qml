import QtQuick 2.0
import QtQuick.Controls 2.2

Button {
    id: control
    contentItem: Text {
        text: control.text
        font: control.font
        color: "white"
        opacity: enabled ? 1.0 : 0.3
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        color: "#20233D"
        radius: 5
    }
}
