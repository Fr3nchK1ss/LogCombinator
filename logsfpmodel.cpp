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
 * ordered by descending timestamp
 */
void LogSFPModel::writeCompoundedLog(const QStringList& filesToCombine, const QString& compoundedLogPath)
{
    sort(0, Qt::DescendingOrder);

    if (QFile compoundedLog(compoundedLogPath); compoundedLog.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )
    {
        QTextStream out(&compoundedLog);

        // Header
        QString decoration1{100,'-'};
        out << decoration1 << Qt::endl
            << "Compounding logs: " << filesToCombine.join(" + ") << Qt::endl
            << Qt::endl
            << decoration1 << Qt::endl;

        // Log lines
        for (int i = 0; i < rowCount(); ++i)
        {
            out << data(index(i,0), LogModel::Timestamp).toString() // Not as QDateTime to have nanosec precision
                << data(index(i,0), LogModel::Filename).toString()
                << data(index(i,0), LogModel::Msg).toString()
                << Qt::endl;
        }

    }
}
