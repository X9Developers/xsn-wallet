import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

ComboBox {
    id: control

    Layout.fillWidth: true

    delegate: ItemDelegate {
        width: control.width

        ComboBoxItem {
            coinName: model.name
            coinIconPath: model.iconPath
            coinAmount: model.amount
            coinValue: model.value
        }

        highlighted: control.highlightedIndex === index
    }

    indicator: Canvas {
        id: canvas
        x: control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2
        width: 12
        height: 8
        contextType: "2d"

        Connections {
            target: control
            onPressedChanged: canvas.requestPaint()
        }

        onPaint: {
            context.reset();
            context.moveTo(0, 0);
            context.lineTo(width, 0);
            context.lineTo(width / 2, height);
            context.closePath();
            context.fillStyle = "#8692C3"
            context.fill();
        }
    }

    contentItem:  ComboBoxItem {
        property var currentItem : control.model.get(control.currentIndex)
        coinName: currentItem.name
        coinIconPath: currentItem.iconPath
        coinAmount: currentItem.amount
        coinValue: currentItem.value
        border.color: "#090D1C"
    }
}
