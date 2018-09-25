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
        color: "white"
        opacity: 0.2
        font.pixelSize: 22
        font.family: "Helvetica"
    }

    Component {
        id: contactDelegate

        Rectangle {
            id: item
            property bool isCurrentItem: ListView.isCurrentItem
            width: parent.width
            height: columnLayout.height
            color: ListView.isCurrentItem ? "#1C1F24" : "transparent"
            border.width: ListView.isCurrentItem? 0 : 1
            border.color: "#3B4046"

            ColumnLayout {
                id: columnLayout
                width: parent.width

                RowLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 45

                    Layout.leftMargin: 25
                    Layout.rightMargin: 25
                    Layout.topMargin: 5
                    Layout.bottomMargin: 5

                    Item {
                        Layout.preferredWidth: 40
                        Layout.fillHeight: true

                        Text {
                            text: txDate
                            color: "white"
                            font.pixelSize: 15
                            anchors.centerIn: parent
                        }
                    }

                    RowLayout {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Image {
                            Layout.leftMargin: 7
                            Layout.rightMargin: 12
                            source: isSend? "qrc:/images/images.png" : "qrc:/images/received.jpg"
                            sourceSize.width: 16
                            sourceSize.height: 16
                        }

                        Text { text: isSend ? "Sent" : "Received"; color: "white"; font.pixelSize: 15; }
                        Item { Layout.fillHeight: true; Layout.fillWidth: true}
                        Text { text: delta; color: "darkorange"; anchors.right: parent.right}
                    }
                }

                ColumnLayout {
                    Layout.preferredHeight: 100
                    Layout.fillWidth: true

                    anchors.leftMargin: 70
                    anchors.left: parent.left
                    visible: item.isCurrentItem

                    RowLayout {
                        spacing: columnLayout.width / 25

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
                        Column {
                            Text { text: "NOW"; font.bold: true; font.pixelSize: 10; color: "white" }
                            Text { text: "38.43 USD"; font.pixelSize: 10; color: "white" }
                        }
                    }
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
