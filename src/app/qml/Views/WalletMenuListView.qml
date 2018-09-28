import QtQuick 2.0
import QtQuick.Layouts 1.3

import "../Components"

ColumnLayout {
    id: root
    anchors.fill: parent

    property int currentIndex: 0
    property string currentName: "Portfolio"

    property bool isSmallMenu: width === menuWidthSmallMode ? true : false

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "Portfolio"
        imageSource: "qrc:/images/Portfolio.png"
        onMenuItemClicked: { currentIndex = 0 ; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "Wallet"
        imageSource: "qrc:/images/Wallet.png"
        onMenuItemClicked: { currentIndex = 1 ; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "Exchange"
        imageSource: "qrc:/images/Exchange.png"
        onMenuItemClicked: { currentIndex = 2; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "Backup"
        imageSource: "qrc:/images/Backup.png"
        onMenuItemClicked: { currentIndex = 3; currentName = name;}
    }

    Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "Settings"
        imageSource: "qrc:/images/Settings.png"
        onMenuItemClicked: { currentIndex = 4; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: isSmallMenu ? menuItemHeightSmallMode : menuItemHeightLargeMode
        isCurrentItem: currentName === name
        name: "Help"
        imageSource: "qrc:/images/Help.png"
        onMenuItemClicked: { currentIndex = 5; currentName = name}
    }
}

