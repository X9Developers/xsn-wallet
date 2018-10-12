import QtQuick.Controls 2.3
import QtQuick 2.0
import QtQuick.Layouts 1.3

Popup {
    id: popUpComponent
    property alias container: item
    property string popUpText: ""
    closePolicy: Popup.CloseOnEscape

    background: Rectangle {
        id: backgroundRoot
        color: "transparent"
    }

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    parent: Overlay.overlay
    modal: true

    Rectangle {
        id: item
        anchors.fill: parent
        anchors.topMargin: 54
        color: "#16192E"
    }

    RowLayout {
        width: parent.width
        height: 60
        spacing: 115

        XSNLabel {
            text: popUpText
            property int backgroundRectangleWidth: 0
            style: Text.StyledText
            color: "#FFFFFF"
            font.pixelSize: 26
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        RoundButton {
            id: control
            width: 40
            height: 39
            radius: 20
            Layout.alignment: Layout.Right
            background: Rectangle {
                color: "transparent"
                radius: 20
            }

            text: "x"
            font.pixelSize: 22

            contentItem: Label {
                text: control.text
                font: control.font
                color: "#8C9CD4"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            //            background: "#3F444A"
            onClicked: popUpComponent.close()
        }
    }
}

