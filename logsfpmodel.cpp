#include <QDateTime>
#include <QFile>
#include <QTextStream>

#include "logsfpmodel.h"
#include "logmodel.h"


LogSFPModel::LogSFPModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setSortRole(LogModel::LogRoles::Timestamp);
}


/**
 * @brief LogSFPModel::writeCompoundedLog
 * @param filesToCombine: selected by the user in the QML interface
 * @param compoundedLogPath: output path, defined in the logController
 *
 * Write a new log file which contains the logs from all the user selected files,
 * ordered by timestamp
 */
void LogSFPModel::writeCompoundedLog(QStringList filesToCombine, QString compoundedLogPath)
{
    QFile compoundedLog(compoundedLogPath);
    if ( compoundedLog.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )
    {
        QTextStream out(&compoundedLog);

        // Header
        QString decoration1{150, '='};
        out << decoration1 << "\n";
        out << "Compounding logs: ";
        out << filesToCombine.join(" + ") << "\n\n";
        out << decoration1 << "\n";

        for (int i = 0; i < rowCount(); ++i)
        {
            out << data(index(i,0), LogModel::Timestamp).toString() // Not as QDateTime to have nanosec precision
                << data(index(i,0), LogModel::Filename).toString()
                << data(index(i,0), LogModel::Msg).toString()
                << "\n";
        }

    }
}
