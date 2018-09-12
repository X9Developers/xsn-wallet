import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

import "Pages"

Window {
    visible: true
    width: 1100
    height: 640
    title: qsTr("Hello World")

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

