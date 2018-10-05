import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import "../Components"

Item {
    id: root
    property string assetName: ""
    property string assetSymbol: ""
    property QtObject transactionListModel: undefined

    ColumnLayout {
        anchors.fill: parent

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
                anchors.fill: parent
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                spacing: width * 0.02

                Text {
                    Layout.preferredWidth: parent.width * 0.08
                    Layout.alignment: Qt.AlignCenter
                    text: "Type";
                    color: "#7F8DC1";
                    font.pixelSize: 11
                }

                Text {
                    Layout.preferredWidth: parent.width * 0.18
                    text: "Date";
                    color: "#7F8DC1";
                    font.pixelSize: 11
                }

                Text {
                    Layout.preferredWidth: parent.width * 0.16
                    text: "Currency"; color: "#7F8DC1"; font.pixelSize: 11
                }

                Text {
                    Layout.preferredWidth: parent.width * 0.22
                    text: "Transaction ID"; color: "#7F8DC1"; font.pixelSize: 11
                }

                Item {
                    Layout.preferredWidth: parent.width * 0.18
                    Layout.alignment: Qt.AlignRight

                    Text {
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Amount";
                        color: "#7F8DC1";
                        font.pixelSize: 11
                    }
                }

                Item {
                    Layout.preferredWidth: parent.width * 0.06
                }
            }
        }

        XSNLabel {
            visible: transactionsList.count === 0
            anchors.centerIn: parent
            text: "No %1 Transactions".arg(assetName)
            color: "white"
            opacity: 0.2
            font.pixelSize: 22
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
                color: ListView.isCurrentItem ? "#20233D": mouseArea.containsMouse ? "#20233D" : "#16192E"
                radius: 4

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 20
                    anchors.rightMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: width * 0.02

                    Item {
                        Layout.preferredWidth: parent.width * 0.08
                        Layout.alignment: Qt.AlignCenter

                        Image {
                            source: isSend? "qrc:/images/images.png" : "qrc:/images/received.jpg"
                            anchors.verticalCenter: parent.verticalCenter
                            sourceSize.width: 25
                            sourceSize.height: 25
                        }
                    }

                    Column {
                        Layout.preferredWidth: parent.width * 0.18
                        Layout.alignment: Qt.AlignVCenter

                        Text { text: isSend ? "Sent" : "Received"; color: "white"; font.pixelSize: 14}
                        Text { text: txDate; color: "#7D8CBF"; font.pixelSize: 11}
                    }

                    Row {
                        Layout.preferredWidth: parent.width * 0.16
                        Layout.alignment: Qt.AlignVCenter
                        spacing: 7

                        Image {
                            anchors.verticalCenter: parent.verticalCenter
                            source: "qrc:/images/%1.png" .arg(assetName)
                            sourceSize: Qt.size(25, 25)
                        }

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: assetName
                            color: "white"
                            font.pixelSize: 14
                        }
                    }

                    Row {
                        Layout.preferredWidth: parent.width * 0.22
                        Layout.alignment: Qt.AlignVCenter
                        spacing: width * 0.05

                        Text {
                            property string iD: "dfjvndskfjnvdskjfvndskfvnbdskfnvkfdv"
                            id: transactionID
                            width: parent.width * 0.8
                            text: iD//id
                            color: "#7D8CBF"
                            font.pixelSize: 14
                            elide: Text.ElideRight
                        }

                        Image {
                            width: transactionID.height
                            visible: mouseArea.containsMouse
                            source: "qrc:/images/copy.png"
                            sourceSize: Qt.size(20, 20)
                            height: transactionID.height
                        }
                    }

                    Column {
                        Layout.preferredWidth: parent.width * 0.18
                        Layout.alignment: Qt.AlignVCenter

                        Row {
                            anchors.right: parent.right
                            spacing: 5
                            Text { text: isSend ? "−" : "+"; color: isSend ? "#E2344F": "#1DB182"; font.pixelSize: 14}
                            Text { text: delta; color: isSend ? "#E2344F": "#1DB182"; font.pixelSize: 14}
                            Text { text: assetSymbol; color: isSend ? "#E2344F": "#1DB182"; font.pixelSize: 14; font.capitalization: Font.AllUppercase}
                        }

                        Text {
                            anchors.right: parent.right
                            text: "$ 4562.54"; color: "#7D8CBF"; font.pixelSize: 11;
                        }
                    }

                    Item {
                        Layout.preferredWidth: parent.width * 0.06

                        Image {
                            id: image
                            anchors.centerIn: parent
                            sourceSize: Qt.size(20, 20)
                            source: "qrc:/images/checkmark.png"
                        }

                        ColorOverlay {
                            anchors.fill: image
                            source: image
                            color: "#1DB182"
                        }
                    }
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
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

