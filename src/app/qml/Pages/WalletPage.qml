import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import "../Views"
import "../Components"
import "../Popups"

import com.xsn.viewmodels 1.0
import com.xsn.models 1.0

Page {
    id: root
    property int windowWidth: 0
    property int currentAssetID: assetsListView.currentItem ? assetsListView.currentItem.id : 0
    property string currentAssetName: assetsListView.currentItem ? assetsListView.currentItem.name : ""
    property string currentAssetColor: assetsListView.currentItem ? assetsListView.currentItem.color : ""
    property string currentAssetSymbol: assetsListView.currentItem ? assetsListView.currentItem.symbol : ""

    background: Rectangle {
        color: "transparent"
    }

    WalletAssetViewModel {
        id: walletViewModel
        Component.onCompleted: {
            initialize(ApplicationViewModel);
        }
        currentAssetID: root.currentAssetID
    }

    ColumnLayout {
        anchors.fill: parent

        anchors.leftMargin: 30
        anchors.rightMargin: 30
        anchors.bottomMargin: 30
        spacing: 35

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 45

            LinearGradient {
                id: background
                anchors.fill: parent
                start: Qt.point(0, 0)
                end: Qt.point(width, 0)
                gradient: Gradient {
                    GradientStop { position: 1.0; color: "transparent" }
                    GradientStop { position: 0.0; color:  "#0D1E3D"}
                }
            }

            RowLayout {
                anchors.fill: parent

                WalletAssetsListView {
                    id: assetsListView
                    anchors.fill: parent
                    model: WalletAssetsListModel {
                        Component.onCompleted: initialize(ApplicationViewModel)

                        onModelReset: {
                            assetsListView.currentIndex = 0;
                        }
                    }
                }
            }

        }
        WalletPageHeaderView {
            //Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.preferredHeight: headerViewHeightSmallMode/*windowWidth > windowWidthSmallMode ? (width > windowWidthLargeMode ? headerViewHeightLargeMode : headerViewHeightMediumMode)
                                                          : headerViewHeightSmallMode*/
            coinMeasure: currentAssetName
            labelColor: currentAssetColor
            coinSymbol: currentAssetSymbol
            windowWidth: root.windowWidth

            onSendCoins: {
                openSendDialog({});
            }


            onReceiveCoins: {
                openReceiveDialog({});
            }
        }

        TransactionsListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            transactionListModel: walletViewModel.transactionsListModel

            onTransactionDetails: {
                openTransactionDetailsDialog({});
            }
        }
    }
}
