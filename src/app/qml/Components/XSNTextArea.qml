import QtQuick 2.0
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

ColumnLayout{

    XSNLabel {
        Layout.leftMargin: 30
        color: "#8C9CD4"
        font.pixelSize: 12
        text: qsTr("Send funds to")
    }

    Rectangle {

        Layout.leftMargin: 30
        color: "#090D1C"
        Layout.preferredWidth: 400
        Layout.preferredHeight: 30

        TextArea {
            Layout.leftMargin: 31
            font.bold: false;
            font.pixelSize: 14;
            color: "#454C71"
            placeholderText: "Enter the XSN address"

            cursorVisible: true
        }
    }
}
