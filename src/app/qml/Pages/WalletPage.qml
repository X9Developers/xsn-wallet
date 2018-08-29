import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Views"
import "../Components"
import com.xsn.viewmodels 1.0

Page {

    WalletAssetViewModel {
        id: walletViewModel
    }

    RowLayout {
        anchors.fill: parent

        WalletAssetsListView {
            Layout.fillHeight: true
            Layout.maximumWidth: parent.width / 4
            Layout.minimumWidth: parent.width / 4
        }

        ColumnLayout{

            Layout.fillWidth: true
            Layout.fillHeight: true

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "grey"

                ColumnLayout{

                    anchors.fill: parent

                    //                    Item {
                    //                        Layout.fillHeight: true
                    //                    }

                    IconButton {
                        id: logBut
                        source: "qrc:/images/BC_Logo_.png"
                        sourceSize: Qt.size(55, 55)
                        anchors.horizontalCenter: parent.horizontalCenter

                        hoverEnabled: true
                        onHoveredChanged: {
                            if(logBut.hovered)
                            {
                                logBut.source = "qrc:/images/refresh.png"
                            }
                            else
                            {
                                logBut.source = "qrc:/images/BC_Logo_.png"
                            }
                        }
                    }

                    Text {
                        text: qsTr("0.01347051 BTC")
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: "Helvetica"
                        font.pixelSize: 30
                        style: Text.StyledText
                        color: "Orange"
                        styleColor: "black"
                    }

                    Text {
                        text: qsTr("$91.22 USD")
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: "Helvetica"
                        font.pixelSize: 30
                        style: Text.StyledText
                        color: "white"
                        styleColor: "black"
                    }

                    Item {
                        Layout.fillHeight: true
                    }


                    RowLayout{

                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.bottomMargin

                        TransactionButton{
                            Layout.preferredWidth: 80
                            color: "orange"
                            radius: 20
                            text: qsTr("Send")
                        }

                        TransactionButton{
                            Layout.preferredWidth: 80
                            color: "orange"
                            radius: 20
                            text: qsTr("Receive")
                        }
                    }
                }

            }

            TransactionsListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: parent.height / 2

            }
        }
    }
}
