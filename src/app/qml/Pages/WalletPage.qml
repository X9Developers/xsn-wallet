import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Views"

Page {

    RowLayout {
        anchors.fill: parent

        WalletAssetsListView {
            Layout.fillHeight: true
            Layout.maximumWidth: parent.width / 4
//            Layout.minimumWidth: /*width / 4*/
            Layout.fillWidth: true
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "grey"
        }
    }
}
