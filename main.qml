import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("SIMULinho")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Parametros")
                width: parent.width
                onClicked: {
                    stackView.push("PageParametros.ui.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Core")
                width: parent.width
                onClicked: {
                    stackView.push("PageCore.ui.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "Home.ui.qml"
        anchors.fill: parent
    }
}