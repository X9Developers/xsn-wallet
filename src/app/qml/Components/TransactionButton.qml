import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0


Button {
    id:actionButton

    //property alias text : buttonText.text
    property color color: "transparent"
    property int radius: 0

    background: Rectangle {
        color: actionButton.color
        radius: actionButton.radius
    }

//    Text {
//            id: buttonText
//            text: parent.description
//            anchors.centerIn: parent
//            font.pixelSize: parent.height * .5
//            style: Text.Sunken
//            color: "white"
//            styleColor: "black"
//        }
}
