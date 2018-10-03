import QtQuick 2.0
import QtQuick.Layouts 1.3

import "../Components"

Item {
    id: root
    property string assetName: ""
    property QtObject transactionListModel: undefined

    ColumnLayout {
        anchors.fill: parent
        anchors.centerIn: parent

        XSNLabel {
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            Layout.topMargin: 10
            Layout.bottomMargin: 10
            Layout.rightMargin: 10
            Layout.alignment: Qt.AlignVCenter

            text: "Transactions"
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            color: "#20233D"
            radius: 4

            RowLayout {
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                anchors.fill: parent
                Layout.alignment: Qt.AlignVCenter

                Text {
                    Layout.preferredWidth: 30
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignHCenter
                    text: "Type"; color: "#7F8DC1"; font.pixelSize: 10
                }
                Text {
                    Layout.preferredWidth: 60
                    Layout.fillHeight: true
                    //ayout.alignment: Qt.AlignLeft
                    text: "Date"; color: "#7F8DC1"; font.pixelSize: 10
                }
                Text {
                    Layout.preferredWidth: 60
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignLeft
                    text: "Currency"; color: "#7F8DC1"; font.pixelSize: 10
                }
                Text {
                    Layout.preferredWidth: 60
                    Layout.fillHeight: true
                    //Layout.alignment: Qt.AlignLeft
                    text: "Transaction ID"; color: "#7F8DC1"; font.pixelSize: 10
                }

                Text {
                    Layout.preferredWidth: 60
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignRight
                    text: "Amount"; color: "#7F8DC1"; font.pixelSize: 10
                }

                Item {
                    Layout.preferredWidth: 20
                    Layout.fillHeight: true
                }
            }
        }

        ListView {
            id: transactionsList

            Layout.fillHeight: true
            Layout.fillWidth: true

            boundsBehavior: Flickable.StopAtBounds
            model: transactionListModel
            clip: true

            delegate: contactDelegate

            focus: true
            spacing: 5

            add: Transition {
                NumberAnimation { properties: "y"; from: transactionsList.height; duration: 200 }
            }
            addDisplaced: Transition {
                NumberAnimation { properties: "x,y"; duration: 200 }
            }
        }


        Component {
            id: contactDelegate

            Rectangle {
                id: item
                property bool isCurrentItem: ListView.isCurrentItem
                width: parent.width
                height: closedTransactionHeight
                color: "#16192E"
                radius: 4

                RowLayout {
                    anchors.fill: parent

                    Layout.leftMargin: 20
                    Layout.rightMargin: 20

                    Item {
                        Layout.preferredWidth: 40
                        Layout.fillHeight: true

                        Image {
                            source: isSend? "qrc:/images/images.png" : "qrc:/images/received.jpg"
                            anchors.centerIn: parent
                            sourceSize.width: 16
                            sourceSize.height: 16
                        }
                    }

                    Column {
                        Layout.preferredWidth: 100
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignVCenter

                        Text { text: isSend ? "Sent" : "Received"; color: "white"; font.pixelSize: 15; }
                        Text { text: txDate; color: "white"; font.pixelSize: 10;}
                    }

                    Row {
                        Layout.preferredWidth: 125
                        Layout.fillHeight: true

                        Image {
                            source: "qrc:/images/Bitcoin.png"
                            sourceSize: Qt.size(15, 15)
                        }

                        Text { text: "Currency"; color: "white"; font.pixelSize: 10}
                    }

                    Text {
                        Layout.preferredWidth: 125
                        Layout.fillHeight: true
                        text: id
                        color: "grey"
                        font.pixelSize: 12
                    }

                    Column {
                        Layout.preferredWidth: 60
                        Layout.fillHeight: true

                        Row {
                            Text { text: isSend ? "−" : "+"; color: isSend ? "#1DB182" : "#E2344F"; font.pixelSize: 12}
                            Text { id: deltaData; text: delta; color: isSend ? "#1DB182" : "#E2344F"; font.pixelSize: 12}
                        }

                        Text {
                            text: "$ 4562.54"; color: "white"; font.pixelSize: 10;
                        }
                    }

                    Item {
                        Layout.preferredWidth: 20
                        Layout.fillHeight: true
                    }
                }


                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(transactionsList.currentIndex === index)
                            transactionsList.currentIndex = -1
                        else
                            transactionsList.currentIndex = index
                    }
                }
            }
        }
    }
}

