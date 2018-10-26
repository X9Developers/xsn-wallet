import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

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

                MouseArea {
                    anchors.fill: parent
                    onClicked: searchArea.text !== "" ? searchWallet() : showAllWallets()
                }
            }

            TextField {
                id: searchArea
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 15
                textColor: "white"
                placeholderText: "Search wallet"

                FontLoader { id: localFont; source: "qrc:/Rubik-Regular.ttf" }
                font.family: localFont.name

                style: TextFieldStyle
                {
                    placeholderTextColor: "#8C9CD4"
                    background: Rectangle {
                        color: "transparent"
                    }
                }
                onTextChanged: searchArea.text !== "" ? searchWallet() : showAllWallets()
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

    function existWallet()
    {
        var walletName = searchArea.text.replace(/ /g,'').toLowerCase();
        for (var entry = 0; entry < walletsListModel.model.count; entry++)
        {
            if(walletsListModel.contentItem.children[entry].name.toLowerCase() === walletName)
                return entry
        }

        return -1;
    }

    function searchWallet()
    {
        var walletIndex = existWallet()
        for (var entry = 0; entry < walletsListModel.model.count; entry++)
        {
            if(entry !== walletIndex)
            {
                walletsListModel.contentItem.children[entry].visible = false;
                walletsListModel.contentItem.children[entry].height = 0
            }
            else
            {
                walletsListModel.contentItem.children[entry].visible = true;
                walletsListModel.contentItem.children[entry].height = closedTransactionHeight
            }
        }
    }

    function showAllWallets()
    {
        for (var entry = 0; entry < walletsListModel.model.count; entry++)
        {
            walletsListModel.contentItem.children[entry].visible = true;
            walletsListModel.contentItem.children[entry].height = closedTransactionHeight
        }
    }
}
