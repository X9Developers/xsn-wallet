import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../Views"
import "../Components"

import com.xsn.viewmodels 1.0

Page {
    property string modelName: undefined
    EmulatorViewModel {
        id: walletViewModel
        applicationViewModel: ApplicationViewModel
    }

    EmulatorView {
        id: emulatorView
        anchors.fill: parent
        onAddTransaction: walletViewModel.addTransaction(modelName);
    }
}
