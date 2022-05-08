import QtQuick 2.0
import QtQuick.Controls

Button {
    contentItem: Text {
        text: "Combine"
        color: "green"
        font.pixelSize: 26
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        id: backgroundRect
        border.width: 0
        implicitHeight: 80
        implicitWidth: 200
    }

}

