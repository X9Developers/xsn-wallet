import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Components"

ColumnLayout {
    spacing: 40

    Column {
        Layout.fillWidth: true
        Layout.preferredHeight: 50

        XSNLabel {
            text: "Currency"
            font.pixelSize: 25
        }

        XSNLabel {
            text: "Set your preferred local currency"
            font.pixelSize: 15
        }

        ComboBox {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: ["Japanese", "South Korean", "United States"]
        }
    }
}
