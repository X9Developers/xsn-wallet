import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.3

import "../Components"

ListView {
    id: transactionsList

    Layout.fillHeight: true
    Layout.fillWidth: true

    boundsBehavior: Flickable.StopAtBounds
    clip: true

    model: ["1"]

    delegate: Rectangle {
        color: "#16192E"
        width: parent.width

        RowLayout {
            anchors.fill: parent

            Row {
                spacing: 5
                RoundButton {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 16
                    height: 16
                    radius: height / 2
                }

                Column {
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

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Column {
                spacing: 5
                Row {
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
                    anchors.right: parent.right
                    text: "$ 4562.54"
                }
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            SecondaryLabel {
                text: "12%"
                Layout.alignment: Qt.AlignVCenter
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Row {
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

