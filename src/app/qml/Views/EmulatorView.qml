import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Rectangle {
    id: root
    anchors.fill: parent

    property var transactionListModel: undefined
    signal addTransaction();

    ColumnLayout {
        spacing: 20
        width: parent.width
        height: parent.height

        Rectangle {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 150
            Layout.preferredHeight: 70

            color: "transparent"

            Button {
                id: addTransaction
                anchors.fill: parent
                text: "Add transaction"
                onClicked: root.addTransaction();
                anchors.topMargin: 10
                anchors.bottomMargin: 25
            }
        }

        Text {
            Layout.preferredWidth: 100
            Layout.preferredHeight: 20
            Layout.alignment: Qt.AlignHCenter

            text: qsTr("Transaction list")
            font.pointSize: 12

        }

        Rectangle {
            Layout.alignment: Qt.AlignLeft
            Layout.fillHeight: true
            Layout.fillWidth: true

            color: "white"

            ColumnLayout {
                id: layout
                spacing: 0
                anchors.fill: parent.fill
                height: parent.height
                width: parent.width

                ListView {
                    boundsBehavior: Flickable.StopAtBounds
                    anchors.fill: parent
                    model: transactionListModel
                    //focus: true
                    clip: true
                    delegate: Item {
                        width: 200; height: 80
                        anchors.bottomMargin: 5
                        Column {
                            Text { text: '<b>ID:</b> ' + id }
                            Text { text: isSend ?'<b>Type:</b> ' + "Send": '<b>Type:</b> ' + "Received"}
                            Text { text: '<b>Delta:</b> ' + delta }
                        }
                    }
                }
            }
        }
    }
}
