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
    background: Rectangle {
        color: "transparent"
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

            SettingsHeader {
                id: settingsHeader
            }
        }

        SettingsView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: settingsHeader.actualIndex

            Rectangle {
                anchors.fill: parent
                color: "red"
            }
        }
    }
}

