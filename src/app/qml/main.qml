import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

import "Pages"

Window {
    visible: true
    width: 1100
    height: 640
    title: qsTr("Hello World")

   MainPage {
       anchors.fill: parent
   }
}
