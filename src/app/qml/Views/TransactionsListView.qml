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

        Rectangle{
            color: "white"
            border.width: 1
            border.color: "black"
            width: parent.width
            height: ListView.isCurrentItem ? 70 : 20
            MouseArea {
                anchors.fill: parent
                onClicked: { transactionsList.currentIndex = index }
            }

            ColumnLayout{
                width: parent.width
                height: parent.height


//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: { transactionsList.currentIndex = index }
//                }

                RowLayout {
                    //width: parent.width
                    //height: parent.height

                    Text { text: txDate }
                    Image {
                        source: isSend? "qrc:/images/images.png" : "qrc:/images/received.jpg"
                        sourceSize.width: 16
                        sourceSize.height: 16
                    }

                    Text { text: isSend ? "Sent" : "Received" }
                    Text { text: qsTr("Id: ") + id }
                    Item { Layout.fillWidth: true }
                    Text { text: delta }

                }

                GridLayout{
                    columns: 3

                   // visible: !ListView.isCurrentItem //transactionsList.i

                    Text { text: "Friday, Jun 15th 2018, 11:23:01 PM"; font.pixelSize: 12 }
                    Text { text: "f4184fc596403b9d638783cf57adfe4c75"; font.pixelSize: 12}
                    Text { text: "4ce18f49ba153a51bcda9bb80d7f978e3d"; font.pixelSize: 12}
                    Text { text: "38.43 USD"; font.pixelSize: 12 }

                }
            }

        }
    }



    ListView {
        id:transactionsList
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        anchors.fill: parent
        model: transactionListModel
        delegate: contactDelegate
        focus: true
        spacing: 7
        //height: ListView.isCurrentItem ? 20 : 60
    }

}
