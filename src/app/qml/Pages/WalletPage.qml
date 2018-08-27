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
            //            Layout.fillWidth: true
        }

        ColumnLayout{

            Layout.fillWidth: true
            Layout.fillHeight: true

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "grey"

                Text {
                    anchors.centerIn: parent
                    text: "Balance: " + walletViewModel.balance
                }

                TransactionButton{
                    textButton: "Send"
                }

                TransactionButton{
                    textButton: "Receive"
                }

                Image {
                    //source: "pics/qtlogo.png"
                }

            }

            TramsactionsListView {
                //anchors.fill: parent
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: parent.height / 2

            }
        }

    }
}
