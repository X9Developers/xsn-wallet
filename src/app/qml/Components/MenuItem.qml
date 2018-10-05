import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Item {
    id: root
    signal menuItemClicked()
    property bool isCurrentItem: false
    property bool isSmallItem: parent.isSmallMenu

    property string name: ""
    property string imageSource: ""

    property color currentColor: isCurrentItem ? "#2C80FF" : mouseArea.containsMouse ? "lightgrey" :  "grey"

    LinearGradient {
        anchors.fill: parent
        start: Qt.point(0, 0)
        end: Qt.point(width, 0)
        gradient: Gradient {
            GradientStop { position: 1.0; color: "transparent" }
            GradientStop { position: 0.0; color: isCurrentItem ? "#0D1A35" : "transparent" }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.centerIn: parent

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            visible: root.isSmallItem

            MenuIcon {
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                Layout.alignment: Qt.AlignHCenter
                source: imageSource
                color: currentColor
            }

            Text {
                Layout.alignment: Qt.AlignHCenter
                text: name
                font.pixelSize: 13
                color: currentColor
            }
        }

        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.leftMargin: 25
            visible: !root.isSmallItem

            MenuIcon {
                Layout.preferredWidth: implicitWidth
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignVCenter
                source: imageSource
                color: currentColor
            }

            Text {
                Layout.alignment: Qt.AlignVCenter
                Layout.leftMargin: 5
                text: name
                font.pixelSize: 14
                color: currentColor
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: menuItemClicked()
    }
}
