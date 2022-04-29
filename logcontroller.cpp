#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>
#include <QTextStream>

#include "logcontroller.h"


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

    populateModel(logModel);
    writeCompoundedLog(logModel);
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
        // rxLogLine matches following entries
        //   (YYYY-MM-DDT)(HH::MM::ss.mmmnnn)(message)
        //   ()(HH::MM::ss.mmmnnn)(message)
        const QRegularExpression rxLogLine("(^.{0,10}T{0,1})(\\d{2}:\\d{2}:\\d{2}\\.\\d{6})(.*)");

        while ( !in.atEnd() )
        {
            const QString line = in.readLine();

            QRegularExpressionMatch match = rxLogLine.match(line);
            if (match.hasMatch())
            {
                const QString timestamp = match.captured(2);
                const QString logMessage = match.captured(3);

                if ( ! (timestamp.isEmpty() || logMessage.isEmpty()) ) // discard non-timestamped & blank lines
                {
                    /*
                    // Filter out some log messages if need, which are in a 'filters' stringlist
                    if ( std::any_of(filters.begin(),
                                     filters.end(),
                                     [&logMessage](const auto& filter){ return QRegularExpression(filter).match(logMessage).hasMatch(); }
                                    ))
                        continue;
                    */

                    model.insertLogLine( { timestamp, " [" + baseLogName.leftJustified(12, ' ', true) + "] ", logMessage });
                }
            }
        }
    }
}


/**
 * @brief LogController::writeCompoundedLog
 * @param logModel
 *
 * Write a new log file which contains the log lines from all the combined file,
 * ordered by timestamp
 */
void LogController::writeCompoundedLog(const LogModel &logModel)
{
    QFile compoundedLog(m_compoundedLogPath);
    if ( compoundedLog.open(QIODevice::ReadWrite) )
    {
        QTextStream out(&compoundedLog);

        // Header
        QString decoration1{150, '='};
        out << decoration1 << "\n";
        out << "Compounding logs: ";
        out << m_filesToCombine.join(" + ") << "\n\n";
        out << decoration1 << "\n";

        logModel.writeOut(out);

    }
}
