import QtQuick
import Qt.labs.folderlistmodel
import QtQuick.Controls

Window {
    id: mainWindow
    minimumWidth: 300
    minimumHeight: 400
    title: "Log Combinator"


    // Eye candy background which is reset() for user feedback
    ParticlesRain {
        id: rain
        anchors.fill: parent
    }


    // Checklist of .log files which can be combined
    ListView {
        width: 200
        height: 20 * logFolderModel.count
        anchors.top: mainWindow.contentItem.top
        anchors.topMargin: 20
        anchors.horizontalCenter: mainWindow.contentItem.horizontalCenter
        interactive: false

        spacing: 10

        // FolderListModel QML properties list:
        // fileName,filePath,fileUrl,fileBaseName,fileSuffix,fileSize,fileModified,fileAccessed,fileIsDir
        model: FolderListModel {
            id: logFolderModel
            showDirs: false
            folder: "file:../LogCombinator"
            nameFilters: ["*.log"]
        }

        delegate: CheckboxDelegate {
            id: logCheckboxDelegate
            checkText: fileName

            // Register files to be combined on c++ side
            onToggled: (logFilePath, isChecked) => logController.registerLogFile(logFilePath, isChecked);
        }

    }


    CombineButton {
        id: combineButton
        anchors.bottom: mainWindow.contentItem.bottom
        anchors.horizontalCenter: mainWindow.contentItem.horizontalCenter
        width: parent.width

        Component.onCompleted: {
            // mainWindow.showMinimized(); // May be necessary on Windows OS
            mainWindow.showNormal();
        }

        // without FX
        // onClicked: {  logController.combineFiles(); // c++ call }

        // with FX
        // * the particle system is reset
        // * the button turns white on green
        onClicked: {
            rain.reset()
            contentItem.color = "white"
            background.color = "green"
            delayTimer.start()
        }

        Timer {
            id: delayTimer
            interval: 100;
            running: false;
            repeat: false
            onTriggered: {
                logController.combineFiles(); // c++ call
                combineButton.contentItem.color = "green"
                combineButton.background.color = "white"
            }
        }
        // end FX
    }

}
