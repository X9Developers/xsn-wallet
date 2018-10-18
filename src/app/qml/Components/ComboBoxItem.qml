import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Rectangle {
    anchors.fill: parent
    color: "#090D1C"
    border.color: "#FFFFFF"

    property string coinName: ""
    property string coinAmount: ""
    property string coinIconPath: ""
    property string coinValue: ""

    RowLayout{
        anchors.fill: parent

        Image {
            Layout.leftMargin: 10
            source: coinIconPath
            sourceSize: Qt.size(16, 16)
        }

        Text {
            id: name
            text: coinName
            font.bold: true
            color: "#FFFFFF"

        }

        Item{
            Layout.fillWidth: true
            Layout.fillHeight: true
        }


        Item{
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        SecondaryLabel{
            font.pixelSize: 12
            text: coinAmount + qsTr(" ") + coinValue
        }

        RoundedImage {
            Layout.rightMargin: 10
            imageSource: "qrc:/images/check@2x.png"
            sourceSize: Qt.size(10, 10)
        }
    }
}
