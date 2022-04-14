#include "logcontroller.h"

LogController::LogController(QObject *parent):
    QObject{parent}
{

}

void LogController::registerLogFile(QString logFile, bool isChecked)
{
    qDebug() << logFile << " - " << isChecked;
    if (isChecked)
        filesToCombine << logFile;
    else
        filesToCombine.removeOne(logFile);
}
