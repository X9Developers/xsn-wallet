import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../Components"

import com.xsn.viewmodels 1.0
import com.xsn.models 1.0

ColumnLayout {
    id: root
    property string accountBalance: walletsListModel.model.accountBalance !== undefined ? walletsListModel.model.accountBalance.toString() : ""

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

            TextField {
                id: searchArea
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 15
                placeholderText: "Search wallet"

                FontLoader { id: localFont; source: "qrc:/Rubik-Regular.ttf" }
                font.family: localFont.name

                color: "#8C9CD4"
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
                id: comboBox
                anchors.verticalCenter: parent.verticalCenter
                model: ["Currency", "Balance"]
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
            onSendCoinsRequested: {
                openSendDialog();
            }
            onReceiveCoinsRequested: {
                openReceiveDialog();
            }

            AssetsListProxyModel {
                id: assetListProxyModel

                source: WalletAssetsListModel {
                    Component.onCompleted: initialize(ApplicationViewModel)
                }
                sortRole: comboBox.currentText === "Balance" ? "balance" : "name"
                filterString: searchArea.text
                filterCaseSensitivity: Qt.CaseInsensitive
                sortCaseSensitivity: Qt.CaseInsensitive
            }

            model: assetListProxyModel
        }
    }
}
