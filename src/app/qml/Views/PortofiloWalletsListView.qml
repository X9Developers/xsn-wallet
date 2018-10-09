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
            text: "Wallets"
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        SecondaryLabel {
            text: qsTr("Sort by")
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
