import QtQuick.Controls 2.2
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

    Rectangle {
        id: item
        anchors.fill: parent
        anchors.topMargin: 40
        color: "#3F444A"
    }

    Item {
        anchors.fill: parent

        RoundButton {
            width: 32
            height: 32
            radius: 24
            background: Rectangle {
                color: "#3F444A"
                radius: 24
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
