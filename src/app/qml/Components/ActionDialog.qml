import QtQuick.Controls 2.3
import QtQuick 2.0
import QtQuick.Layouts 1.3

Popup {
    id: popUpComponent
    property alias container: item

    property string imageSource: ""
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
        anchors.topMargin: 40
        color: "#3F444A"
    }

    Item {
        anchors.fill: parent

        RoundButton {
            id: control
            width: 32
            height: 32
            radius: 24
            background: Rectangle {
                color: "#3F444A"
                radius: 24
            }

            text: "X"
            font.pixelSize: 14

            contentItem: Label {
                text: control.text
                font: control.font
                color: "white"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

//            background: "#3F444A"
            onClicked: popUpComponent.close()
        }

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            sourceSize.width: 50
            sourceSize.height: 50
            source: "qrc:/images/Bitcoin.png"
            //source: imageSource
        }
    }

}
