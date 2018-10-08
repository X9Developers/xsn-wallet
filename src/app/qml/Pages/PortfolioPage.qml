import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

import "../Views"
import "../Components"
import "../Popups"

import com.xsn.viewmodels 1.0
import com.xsn.models 1.0

Page {
    id: root

    background: Rectangle {
        anchors.fill: parent
        color: "#090D1C"
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 30
        spacing: 35

        PageHeaderView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            mainHeader: "Statistics"
            buttonsVisible: false
            coinSymbol: "usd"
        }

        PortofiloWalletsListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
