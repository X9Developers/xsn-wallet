import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Rectangle {
    id: root
    anchors.fill: parent
    color: "#3F444A"
    signal addTransaction(int count)
    signal clearTransactions()

    ColumnLayout {
        spacing: 20
        width: parent.width
        height: parent.height

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Button {
            text: "Add transaction"
            Layout.fillWidth: true
            onClicked: addTransaction(1);
        }
        Button {
            text: "Add 10 transactions"
            Layout.fillWidth: true
            onClicked: addTransaction(10);
        }
        Button {
            text: "Add 50 transactions"
            Layout.fillWidth: true
            onClicked: addTransaction(50);
        }
        Button {
            text: "Add 100 transactions"
            Layout.fillWidth: true
            onClicked: addTransaction(100);
        }
        Button {
            text: "Clear transactions"
            Layout.fillWidth: true
            onClicked: clearTransactions();
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
