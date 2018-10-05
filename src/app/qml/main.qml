import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

import "Pages"

Window {
    visible: true
    width: 1080
    height: 840
    minimumWidth: 1080
    minimumHeight: 840
    title: qsTr("Stakenet Wallet")

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"

            MainPage {
                id: mainPage
                anchors.fill: parent
            }
        }

        Rectangle {
            visible: true
            Layout.fillHeight: true
            Layout.maximumWidth: parent.width / 6
            Layout.minimumWidth: parent.width / 6

            EmulatorPage {
                id: emulatorPage
                modelName: mainPage.currentAssetID
                anchors.fill: parent
            }
        }
    }
}

