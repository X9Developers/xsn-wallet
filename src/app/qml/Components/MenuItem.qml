import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    property bool isCurrentItem: false
    property string name: ""
    property string imageSource: ""
    signal menuItemClicked()

    color: isCurrentItem ? "#292E34" : "transparent"

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: parent.width / 7
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        Image {
            Layout.alignment: Qt.AlignLeft
            sourceSize.width: 16
            sourceSize.height: 16
            source: imageSource
        }

        Text {
            text: name
            font.pixelSize: 14
            color: "white"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: menuItemClicked()
        }
    }
}
