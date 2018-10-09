import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.3

import "../Components"

ListView {
    id: listView

    Layout.fillHeight: true
    Layout.fillWidth: true

    boundsBehavior: Flickable.StopAtBounds
    clip: true

    model: ["1"]

    delegate: Rectangle {
        height: closedTransactionHeight
        color: "#16192E"
        radius: 4
        width: parent.width

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 20
            anchors.rightMargin: 20

            Row {
                Layout.preferredWidth: parent.width * 0.2
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignVCenter

                RoundButton {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 16
                    height: 16
                    radius: height / 2
                }

                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 5

                    XSNLabel {
                        font.pixelSize: 14
                        text: "Dash"
                    }

                    SecondaryLabel {
                        text: "DASH"
                    }
                }
            }


            ColumnLayout {
                Layout.preferredWidth:  parent.width * 0.3
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignRight & Qt.AlignVCenter
                spacing: 5

                Row {
                    Layout.alignment: Qt.AlignRight & Qt.AlignVCenter
                    anchors.right: parent.right
                    spacing: 5

                    XSNLabel {
                        font.pixelSize: 14
                        text: "10.43451021"
                    }

                    SecondaryLabel {
                        text: "DASH"
                    }
                }

                SecondaryLabel {
                    Layout.alignment: Qt.AlignRight & Qt.AlignVCenter
                    anchors.right: parent.right
                    text: "$ 4562.54"
                }
            }

            Item {
                Layout.preferredWidth: parent.width * 0.2
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignRight & Qt.AlignVCenter

                SecondaryLabel {
                    text: "12%"
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Item {
                 Layout.fillWidth: true
                 Layout.fillHeight: true
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignHCenter
                spacing: 7

                CheckableButton {
                    text: "Send"
                }

                CheckableButton {
                    text: "Receive"
                }
            }
        }
    }

    focus: true
    spacing: 5

    add: Transition {
        NumberAnimation { properties: "y"; from: transactionsList.height; duration: 200 }
    }
    addDisplaced: Transition {
        NumberAnimation { properties: "x,y"; duration: 200 }
    }
}

