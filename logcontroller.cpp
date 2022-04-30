#include <QDateTime>
#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QUrl>

#include "logcontroller.h"
#include "logsfpmodel.h"


void LogController::registerLogFile(QString logFile, bool isChecked)
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
 */
void LogController::combineFiles()
{
    LogModel logModel;
    LogSFPModel sfpModel;

    populateModel(logModel);
    sfpModel.setSourceModel(&logModel);
    sfpModel.sort(0);
    sfpModel.writeCompoundedLog(m_filesToCombine, m_compoundedLogPath);

    //writeCompoundedLog(logModel);
    qDebug() << QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath()+"/"+"compounded.log"));
}


/**
 * @brief Fill the model from the log files
 *
 */
void LogController::populateModel(LogModel& model)
{
    for(const auto& path : m_filesToCombine)
    {
        // qDebug() << "Adding " << path;
        QFile logFile(path);
        QString baseLogName = QFileInfo(logFile).baseName();

        if ( !logFile.open(QIODevice::ReadOnly) )
        {
            qDebug() << "Could not open logfile: " << baseLogName;
            return;
        }


        QTextStream in(&logFile);
        while ( !in.atEnd() )
        {
            const QString line = in.readLine();

            // Filter out lines which should not be in the model at the first place. The purpose
            // is different from LogSFPModel, where we may want subsets of valid log lines
            QRegularExpressionMatch match = m_rxLogLine.match(line);
            if (match.hasMatch())
            {
                const QString timestamp = match.captured(1);
                const QString logMessage = match.captured(2);

                const auto ISOTimestamp = QDateTime::fromString(timestamp, Qt::ISODateWithMs);
                if ( timestamp.isEmpty() || !ISOTimestamp.isValid()) // discard non-timestamped non-ISO lines
                {
                    qDebug() << "Invalid ISO timestamp: " << timestamp;
                    continue;
                }

                if ( !logMessage.isEmpty() )// discard blank lines
                {
                    /*
                    // Filter out some log messages if need, which are in a 'filters' stringlist
                    if ( std::any_of(filters.begin(),
                                     filters.end(),
                                     [&logMessage](const auto& filter){ return QRegularExpression(filter).match(logMessage).hasMatch(); }
                                    ))
                        continue;
                    */

                    model.insertLogLine( { timestamp, " [" + baseLogName.leftJustified(10, ' ', true) + "] ", logMessage });
                }
            }
        }
    }
}

