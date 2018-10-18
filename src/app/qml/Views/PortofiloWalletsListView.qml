import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../Components"

import com.xsn.viewmodels 1.0
import com.xsn.models 1.0

ColumnLayout {

    RowLayout {
        Layout.fillWidth: true
        Layout.maximumHeight: 48

        XSNLabel {
            Layout.fillWidth: true
            text: "Wallets"
        }
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Row {
            Layout.fillWidth: true
            Layout.maximumHeight: 48
            Layout.alignment: Qt.AlignVCenter
            spacing: 5

            ColorOverlayImage
            {
                imageSize: 35
                width: imageSize
                height: imageSize
                imageSource: "qrc:/images/magnifyingGlass.png"
                color: "#8C9CD4"
            }

            TextArea {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 14
                color: "#8C9CD4"
                placeholderText: "Search wallet or coin"

                background: Rectangle {
                    color: "transparent"
                }
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Row {
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignRight
            spacing: 10

            SecondaryLabel {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Sort by")
            }

            CustomizedComboBox {
                anchors.verticalCenter: parent.verticalCenter
                model: ["Balance", "Currency"]
            }
        }
    }

    ColumnLayout {
        Layout.fillHeight: true

        Layout.fillWidth: true

        WalletsListHeaderView {
            Layout.fillWidth: true
            Layout.preferredHeight: 30
        }

        WalletsListView {
            id: walletsListModel
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: WalletAssetsListModel {
                Component.onCompleted: initialize(ApplicationViewModel)
            }

            onSendCoinsRequested: {
                openSendDialog();
            }
            onReceiveCoinsRequested: {
                openReceiveDialog();
            }
        }
    }
}
