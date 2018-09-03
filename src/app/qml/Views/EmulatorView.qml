import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Rectangle {
    id: root
    anchors.fill: parent

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
    }
}
