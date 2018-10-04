import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import "../Components"

ColumnLayout {
    id: root
    anchors.fill: parent

    property string currentName: root.children[currentIndex].name

    property int currentIndex: 3
    property bool isSmallMenu: width === menuWidthSmallMode ? true : false

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: root.currentName === name
        name: "Portfolio"
        imageSource: "qrc:/images/icons-1 stroke-16px-chart@2x.png"
        onMenuItemClicked: { root.currentIndex = 0 ; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "Send"
        imageSource: "qrc:/images/icons-1 stroke-16px-withdraw@2x.png"
        onMenuItemClicked: { currentIndex = 1 ; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "Receive"
        imageSource: "qrc:/images/icons-1 stroke-16px-deposit@2x.png"
        onMenuItemClicked: { currentIndex = 2 ; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "Wallets"
        imageSource: "qrc:/images/icons-1 stroke-16px-wallet 2@2x.png"
        onMenuItemClicked: { currentIndex = 3 ; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "Transactions"
        imageSource: "qrc:/images/icons-1 stroke-16px-transactions@2x.png"
        onMenuItemClicked: { currentIndex = 4 ; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "Lightning"
        imageSource: "qrc:/images/icons-1 stroke-16px-lightning@2x.png"
        onMenuItemClicked: { currentIndex = 5 ; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "Exchange"
        imageSource: "qrc:/images/Exchange.png"
        onMenuItemClicked: { currentIndex = 6; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "Masternodes"
        imageSource: "qrc:/images/Masternodes.png"
        onMenuItemClicked: { currentIndex = 7; currentName = name;}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "TPoS"
        imageSource: "qrc:/images/icons-1 stroke-16px-currency@2x.png"
        onMenuItemClicked: { currentIndex = 8 ; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: root.SmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: root.currentName === name
        name: "Settings"
        imageSource: "qrc:/images/Settings.png"
        onMenuItemClicked: { root.currentIndex = 9; currentName = name}
    }

    RowLayout {
        Layout.fillWidth: true
        Layout.preferredHeight: 40
        Layout.margins: 15
        visible: !isSmallMenu
        spacing: 20
        Layout.alignment: Qt.AlignHCenter

        Text {
            text: "Privacy"
            color: "grey"
            font.pixelSize: 14
        }

        Text {
           text: "Terms"
           color: "grey"
           font.pixelSize: 14
        }

        Item {
            width: image.sourceSize.width

            Image {
                id: image
                sourceSize: Qt.size(15, 15)
                source: "qrc:/images/icons-2 stroke-16px-menu.png"
            }
            ColorOverlay {
                anchors.fill: image
                source: image
                color: "grey"
            }

        }
    }

    Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
    }
}


