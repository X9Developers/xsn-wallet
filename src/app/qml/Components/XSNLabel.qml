import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

Text {
    FontLoader { id: localFont; source: "qrc:/Rubik-Regular.ttf" }
    font.family: localFont.name
    style: Text.StyledText
    font.pixelSize: 22
    color: "white"
}
