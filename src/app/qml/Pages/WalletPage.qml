import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

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

//    RowLayout {
//        anchors.fill: parent
//        spacing: 0

//        Rectangle {
//            Layout.fillHeight: true
//            Layout.preferredWidth: windowWidth > windowWidthSmallMode ? assetsViewWidthLargeMode : assetsViewWidthSmallMode
//            color: "#16192E"

//            Item {
//                anchors.fill: parent
//                anchors.topMargin: 1

//                WalletAssetsListView {
//                    id: assetsListView
//                    anchors.fill: parent
//                    model: WalletAssetsListModel {
//                        Component.onCompleted: initialize(ApplicationViewModel)

//                        onModelReset: {
//                            assetsListView.currentIndex = 0;
//                        }
//                    }
//                }

//            }
//        }

        ColumnLayout {
            anchors.fill: parent
            Layout.leftMargin: 30
            Layout.rightMargin: 30
            Layout.bottomMargin: 30
            spacing: 35

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 60
                color: "#16192E"

                RowLayout {
                    anchors.fill: parent
                    Item {
                        anchors.fill: parent
                        anchors.topMargin: 1

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
    //}
}
