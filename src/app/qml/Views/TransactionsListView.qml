import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    color: "grey"

    property var transactionListModel: undefined

    Text {
        anchors.centerIn: parent
        text: transactionListModel === undefined ? "No Transactions" : ""
        font.pixelSize: 12
    }

    //    ListModel {
    //        id: listModel
    //        ListElement {
    //            date: "28\nJUL"
    //            operationPic: "qrc:/images/received.jpg"
    //            type: "Received"
    //            transactionAmount: "+0.00435"
    //            fullDate: "Friday, Jul 28th 2018, 11:23:01 PM"
    //            transactionId: "f4184fc596403b9d638783cf57adfe4c75c605f6356fbc91338530e9831e9e16"
    //            transactionIdTo: "4ce18f49ba153a51bcda9bb80d7f978e3de6e81b5fc326f00465464530c052f4"
    //            valueInUSDNow: "38.43 USD"
    //            valueInUSD: "37.31 USD"

    //        }
    //        ListElement {
    //            date: " 15\nJUN"
    //            operationPic: "qrc:/images/images.png"
    //            type: "Sent"
    //            transactionAmount: "-0.00435"
    //            fullDate: "Friday, Jun 15th 2018, 11:23:01 PM"
    //            transactionId: "f4184fc596403b9d638783cf57adfe4c75c605f6356fbc91338530e9831e9e16"
    //            transactionIdTo: "4ce18f49ba153a51bcda9bb80d7f978e3de6e81b5fc326f00465464530c052f4"
    //            valueInUSDNow: "38.43 USD"
    //            valueInUSD: "37.31 USD"
    //        }
    //        ListElement {
    //            date: "7\nJUN"
    //            operationPic: "qrc:/images/received.jpg"
    //            type: "Received"
    //            transactionAmount: "+0.00435"
    //            fullDate: "Friday, Jul 7th 2018, 11:23:01 PM"
    //            transactionId: "f4184fc596403b9d638783cf57adfe4c75c605f6356fbc91338530e9831e9e16"
    //            transactionIdTo: "4ce18f49ba153a51bcda9bb80d7f978e3de6e81b5fc326f00465464530c052f4"
    //            valueInUSDNow: "38.43 USD"
    //            valueInUSD: "37.31 USD"
    //        }
    //    }

    Component {
        id: contactDelegate

        Rectangle {
            color: "transparent"
            border.width: 1
            border.color: "black"
            width: parent.width
            height: ListView.isCurrentItem ? 140 : 30
            clip: true

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(transactionsList.currentIndex === index)
                        transactionsList.currentIndex = -1
                    else
                        transactionsList.currentIndex = index }
            }

            RowLayout {
                anchors.fill: parent
                Text {
                    Layout.fillHeight: true
                    Layout.maximumWidth: parent.width / 7
                    Layout.minimumWidth: parent.width / 7
                    text: txDate
                }

                Rectangle {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "transparent"
                    clip: true

                    ColumnLayout {
                        Layout.alignment: Qt.AlignHCenter
                        anchors.fill: parent
                        spacing: 12

                        RowLayout {
                            Layout.fillWidth: true
                            Layout.maximumHeight: 30
                            Layout.minimumHeight: 30
                            Layout.alignment: Qt.AlignHCenter

                            Image {
                                id: image
                                anchors.leftMargin: 10
                                anchors.rightMargin: 10
                                source: isSend? "qrc:/images/images.png" : "qrc:/images/received.jpg"
                                sourceSize.width: 16
                                sourceSize.height: 16
                                clip: true
                            }
                            Text {anchors.left: image.right; text: isSend ? "Sent" : "Received" }
                            Item {Layout.fillHeight: true; Layout.fillWidth: true}
                            Text {text: delta; color: "darkorange"}
                        }
                        RowLayout {
                            id: sec
                            Layout.fillWidth: true
                            Layout.maximumHeight: parent.height / 3
                            Layout.minimumHeight: parent.height / 3

                            spacing: 20

                            Column {
                                Text { text: "DATE"; font.bold: true; font.pixelSize: 10 }
                                Text {text: "Friday, Jun 15th 2018, 11:23:01 PM"; font.pixelSize: 10}
                            }
                            Column {
                                Text { text: "TRANSACTION ID"; font.bold: true; font.pixelSize: 10 }
                                Text { text: id; font.pixelSize: 10}
                            }
                            Column {
                                Text { text: "TO"; font.bold: true; font.pixelSize: 10 }
                                Text {  text: "4ce18f49ba153a51bcda9bb80d7f978e3d"; font.pixelSize: 10}
                            }
                        }
                        RowLayout {
                            Layout.fillWidth: true
                            Layout.maximumHeight: parent.height / 3
                            Layout.minimumHeight: parent.height / 3
                            Column {
                                Text { text: "NOW"; font.bold: true; font.pixelSize: 10 }
                                Text { text: "38.43 USD"; font.pixelSize: 10 }
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
        spacing: 7
    }

}
