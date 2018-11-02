import QtQuick 2.0
import QtQuick.Controls 2.1

ComboBox {
    id: control
    font.pixelSize: 14
    delegate: ItemDelegate {
        width: control.width
        contentItem: XSNLabel {
            text: modelData
            color: "#7F8DC1"
            font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            color: parent.highlighted ? "#20233D" : "#090D1C"
            opacity: 0.5
        }

        highlighted: control.highlightedIndex === index
    }

    contentItem: XSNLabel {
        text: control.displayText
        font: control.font
        color:  "white"
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 90
        implicitHeight: 30
        radius: 2
        color: "#090D1C"
    }

    popup: Popup {
        y: control.height - 1
        width: control.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
            boundsBehavior: Flickable.StopAtBounds
        }

        background: Rectangle {
            radius: 2
            color:  "#20233D"
        }
    }

    indicator: Canvas {
        id: canvas
        x: control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2
        width: 10
        height: 7
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
            context.fillStyle = control.pressed ? "white" : "#8C9CD4";
            context.fill();
        }
    }
}

