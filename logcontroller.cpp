#include <QDateTime>
#include <QDesktopServices>
#include <QDir>
#include <QUrl>

#include "logcontroller.h"
#include "logsfpmodel.h"


/**
 * @brief LogController::registerLogFile
 *
 */
void LogController::registerLogFile(const QString logFile, bool isChecked)
{
    // qDebug() << logFile << " - " << isChecked;
    if (isChecked)
        m_filesToCombine << logFile;
    else
        m_filesToCombine.removeOne(logFile);
}


/**
 * @brief LogController::combineFiles
 *
 * React to user clicking the Combine button
 *
 */
void LogController::combineFiles()
{
    LogModel logModel;
    LogSFPModel sfpModel;

    logModel.populate(m_filesToCombine);
    sfpModel.setSourceModel(&logModel);
    sfpModel.writeCompoundedLog(m_filesToCombine, m_compoundedLogPath);

    /*qDebug() << */QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath()+"/"+"compounded.log"));
}

