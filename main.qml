import QtQuick
import Qt.labs.folderlistmodel
import QtQuick.Controls

Window {
    id: mainWindow
    minimumWidth: 300
    minimumHeight: 400
    title: "Log Combinator"

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

            onToggled: (logFilePath, isChecked) => logController.registerLogFile(logFilePath, isChecked);

            // Component.onCompleted: {
            //    console.log(logCheckboxDelegate.height);
            // }
        }

    }

    CombineButton {
        id: combineButton
        anchors.bottom: mainWindow.contentItem.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: mainWindow.contentItem.horizontalCenter

        Component.onCompleted: {
            // Force the recalculation of mainWindow geometry after adding
            // ListView and CombineButton because of a display bug
            mainWindow.showMinimized();
            mainWindow.showNormal();
        }

        onClicked: {
            logController.combineFiles();
        }
    }



}
