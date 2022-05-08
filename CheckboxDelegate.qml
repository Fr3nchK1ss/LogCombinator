import QtQuick 2.0
import QtQuick.Controls


/**
 * https://doc.qt.io/qt-6/qtquickcontrols2-customize.html#customizing-checkdelegate
 */
Item {
    height: 20
    width: 200
    property alias checkText : checkDelegate.text

    signal toggled(string logFilePath, bool isChecked);

    CheckDelegate
    {
        anchors.fill: parent
        id: checkDelegate

        background: Rectangle {
            anchors.fill: parent
            color: "white"
            opacity: 0.7
        }

        onToggled: {
            parent.toggled(filePath, checked);
        }
    }
}
