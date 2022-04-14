import QtQuick 2.0
import QtQuick.Controls


Button {
    hoverEnabled: false // disable because of MS Windows bug

    contentItem: Text {
        text: "Combine"
        font.pixelSize: 26
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        color: combineButton.down ? "purple" : "mediumpurple"
        radius: 15
        border.width: 0
        implicitHeight: 50
        implicitWidth: 200
    }

}
