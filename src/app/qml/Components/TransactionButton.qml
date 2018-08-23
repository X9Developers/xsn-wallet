import QtQuick 2.0
import QtQuick.Controls 1.4

Item {

    property alias textButton: actionButton.text

    Button {
        id:actionButton
        //text:textButton
    }
}
