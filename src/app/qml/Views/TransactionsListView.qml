import QtQuick 2.0
import QtQuick.Layouts 1.3

import "../Components"

Rectangle {
    color: "#292E34"

    property string assetName: ""
    property QtObject transactionListModel: undefined

    XSNLabel {
        anchors.centerIn: parent
        text: transactionsList.count === 0 ? "No %1 Transactions".arg(assetName) : ""
        font.pixelSize: 24
        color: "grey"
    }

    Component {
        id: contactDelegate

        Rectangle {
            color: ListView.isCurrentItem ? "#1C1F24" : "transparent"
            border.width: ListView.isCurrentItem? 0 : 1
            border.color: "#3B4046"
            width: parent.width
            height: ListView.isCurrentItem ? 145 : 45

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(transactionsList.currentIndex === index)
                        transactionsList.currentIndex = -1
                    else
                        transactionsList.currentIndex = index
                }
            }

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.rightMargin: 10

                Item {
                    Layout.fillHeight: true
                    Layout.maximumWidth: parent.width / 14
                    Layout.minimumWidth: parent.width / 14

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        text: txDate
                        color: "white"
                        font.pixelSize: 15
                    }
                }

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    clip: true

                    ColumnLayout {
                        anchors.fill: parent

                        RowLayout {
                            Layout.fillWidth: true
                            Layout.maximumHeight: 45
                            Layout.minimumHeight: 45
                            Image {
                                Layout.leftMargin: 7
                                Layout.rightMargin: 12
                                source: isSend? "qrc:/images/images.png" : "qrc:/images/received.jpg"
                                sourceSize.width: 20
                                sourceSize.height: 20
                            }
                            Text { text: isSend ? "Sent" : "Received"; color: "white"; font.pixelSize: 15; }
                            Item { Layout.fillHeight: true; Layout.fillWidth: true}
                            Text { text: delta; color: "darkorange"; anchors.right: parent.right}
                        }
                        Item { Layout.fillHeight: true; Layout.fillWidth: true }
                        RowLayout {
                            id: sec
                            Layout.fillWidth: true
                            Layout.maximumHeight: parent.height / 4
                            Layout.minimumHeight: parent.height / 4
                            spacing: 20

                            Column {
                                Text { text: "DATE"; font.bold: true; font.pixelSize: 10; color: "white" }
                                Text { text: "Friday, Jun 15th 2018, 11:23:01 PM"; font.pixelSize: 10; color: "white"}
                            }
                            Column {
                                Text { text: "TRANSACTION ID"; font.bold: true; font.pixelSize: 10; color: "white" }
                                Text { text: id; font.pixelSize: 10; color: "white"}
                            }
                            Column {
                                Text { text: "TO"; font.bold: true; font.pixelSize: 10; color: "white" }
                                Text { text: "4ce18f49ba153a51bcda9bb80d7f978e3d"; font.pixelSize: 10; color: "white"}
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true
                            Layout.maximumHeight: parent.height / 4
                            Layout.minimumHeight: parent.height / 4

                            Column {
                                Text { text: "NOW"; font.bold: true; font.pixelSize: 10; color: "white" }
                                Text { text: "38.43 USD"; font.pixelSize: 10; color: "white" }
                            }
                            Item { Layout.fillWidth: true }
                        }
                    }
                }
            }
        }
    }



    ListView {
        id: transactionsList
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        anchors.fill: parent
        model: transactionListModel
        delegate: contactDelegate
        focus: true

        add: Transition {
            NumberAnimation { properties: "y"; from: transactionsList.height; duration: 200 }
        }
        addDisplaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 200 }
        }
    }
}
