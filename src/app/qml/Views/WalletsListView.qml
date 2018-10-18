import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.3

import "../Components"

ListView {
    id: root
    Layout.fillHeight: true
    Layout.fillWidth: true

    signal sendCoinsRequested(int id)
    signal receiveCoinsRequested(int id)

    boundsBehavior: Flickable.StopAtBounds
    clip: true

    delegate: Rectangle {
        height: closedTransactionHeight
        color: "#16192E"
        radius: 4
        width: parent.width
        property string name: model.name
        property string currency: model.symbol
        property int balance: model.balance === undefined ? 0 : model.balance
        property int portfolioPercent: model.percent
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 20
            anchors.rightMargin: 20

            Row {
                Layout.preferredWidth: parent.width * 0.2
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignVCenter
                spacing: 10

                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/images/%1.png" .arg(name)
                    sourceSize: Qt.size(25, 25)
                }

                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 5

                    XSNLabel {
                        font.pixelSize: 14
                        text: name
                    }

                    SecondaryLabel {
                        text: currency
                        font.capitalization: Font.AllUppercase
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
                        text: balance
                    }

                    SecondaryLabel {
                        text: currency
                        font.capitalization: Font.AllUppercase
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
                    text: "%1%" .arg(portfolioPercent)
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

                SecondaryLabel {
                    text: "Send"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: sendCoinsRequested(0);
                    }
                }

                SecondaryLabel {
                    text: "Receive"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: receiveCoinsRequested(0);
                    }
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

