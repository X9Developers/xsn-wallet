import QtQuick 2.0
import QtQuick.Layouts 1.3

import "../Components"

ColumnLayout {
    id: root
    anchors.fill: parent

    property int currentIndex: 0
    property string currentName: "Portfolio"

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: 40
        isCurrentItem: currentName === name
        name: "Portfolio"
        imageSource: "qrc:/images/images.png"
        onMenuItemClicked: { currentIndex = 0 ; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: 40
        isCurrentItem: currentName === name
        name: "Wallet"
        imageSource: "qrc:/images/received.jpg"
        onMenuItemClicked: { currentIndex = 1 ; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: 40
        isCurrentItem: currentName === name
        name: "Exchange"
        imageSource: "qrc:/images/images.png"
        onMenuItemClicked: { currentIndex = 2; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: 40
        isCurrentItem: currentName === name
        name: "Backup"
        imageSource: "qrc:/images/received.jpg"
        onMenuItemClicked: { currentIndex = 3; currentName = name;}
    }

    Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: 40
        isCurrentItem: currentName === name
        name: "Settings"
        imageSource: "qrc:/images/received.jpg"
        onMenuItemClicked: { currentIndex = 4; currentName = name}
    }

    MenuItem {
        Layout.fillWidth: true
        Layout.preferredHeight: 40
        isCurrentItem: currentName === name
        name: "Help"
        imageSource: "qrc:/images/received.jpg"
        onMenuItemClicked: { currentIndex = 5; currentName = name}
    }
}

