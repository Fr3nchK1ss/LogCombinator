import QtQuick 2.0
import QtQuick.Controls

// https://doc.qt.io/qt-6/qtquickcontrols2-customize.html#customizing-checkdelegate

Item {
    height: 20
    width: 200
    property alias checkText : checkDelegate.text

    signal newCheckedFile(string logFile)

    CheckDelegate {
        anchors.fill: parent
        id: checkDelegate

        background: Rectangle {
            anchors.fill: parent
            color: "transparent"
        }

        onToggled: {
            logController.registerLogFile(filePath, checked);
        }

    }
}
