import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import "../Components"

ActionDialog {
    id: root

    ColumnLayout {

        anchors.fill: root.container
        spacing: 1

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            //anchors.verticalCenter: parent.verticalCenter
            sourceSize.width: 110
            sourceSize.height: 110
            source: "qrc:/images/Code.png"
        }


        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        XSNLabel {
            anchors.horizontalCenter: parent.horizontalCenter
            color: "grey"
            font.pixelSize: 14
            text: qsTr("YOUR BITCOIN ADDRESS")
        }

        XSNLabel {
            anchors.horizontalCenter: parent.horizontalCenter
            color: "orange"
            font.pixelSize: 14
            text: qsTr("1FgxF3zFsmBfU9RXYbCX6JyngMsLvCnT2x")
        }

        RowLayout{
            id: rowLayout

            Layout.fillWidth: true
            Layout.preferredHeight: 60
            spacing: 35

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            RoundedImage {
                imageSource: "qrc:/images/CopyFlat.png"
            }

            RoundedImage {
                imageSource: "qrc:/images/PrintFlat.png"
            }

            RoundedImage {
                imageSource: "qrc:/images/MailFlat.png"
            }

            RoundedImage {
                imageSource: "qrc:/images/ViewFlat.png"
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

        }
    }
}
