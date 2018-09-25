import QtQuick 2.0
import QtQuick.Layouts 1.3
import "../Components"

ActionDialog {
    id: root

    ColumnLayout {

        anchors.fill: root.container
        spacing: 5

        Rectangle {
            width: 50
            height: 50
            color: "red"
        }


        Rectangle {
            width: 50
            height: 50
            color: "blue"
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

//        Image {
//            anchors.horizontalCenter: parent.horizontalCenter
            //anchors.verticalCenter: parent.verticalCenter
//            sourceSize.width: 90
//            sourceSize.height: 90
//            source: "qrc:/images/Bitcoin.png"
//        }

//        Text {
//            id: name
//            text: qsTr("YOUR BITCOIN ADDRESS")
//        }
    }
}
