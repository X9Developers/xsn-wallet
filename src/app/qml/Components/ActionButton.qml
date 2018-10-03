import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3


Button {
    id: actionButton

    property string buttonText: ""
    property string source: ""

    background: Rectangle {
        color: "#20233D"
        radius: 5
    }

    contentItem: RowLayout {
        anchors.fill: parent
        anchors.centerIn: parent.Center
        //Layout.alignment: Qt.AlignVCenter

        Item {
            Layout.preferredWidth: image.sourceSize.width
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignCenter

            Image {
                id: image
                anchors.margins: 10
                anchors.left: parent.left
                anchors.centerIn: parent
                sourceSize: Qt.size(15, 15)
                source: actionButton.source
            }

            ColorOverlay {
                anchors.fill: image
                source: image
                color: "#8C9CD4"
            }
        }

        Text {
            Layout.alignment: Qt.AlignVCenter
            text: actionButton.buttonText
            color: "white"
            font.pixelSize: 14
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: actionButton.clicked()

    }
}

