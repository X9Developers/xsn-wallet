import QtQuick 2.0

Text {
    property int backgroundRectangleWidth: 0
    font.family: "Arial"
    style: Text.StyledText
    styleColor: "black"
    font.pixelSize: 60 //backgroundRectangleWidth !== 0 ? (backgroundRectangleWidth > 930 ? (backgroundRectangleWidth > 1150 ? 80 : 45)
                                                                                    // : 35 )
                                                  // : 35
}
