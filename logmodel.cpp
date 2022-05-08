#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "logmodel.h"


/**
 * @brief Override
 */
QHash<int, QByteArray> LogModel::roleNames() const
{
    QHash<int, QByteArray> mapping {
        {Timestamp, "timestamp"},
        {Filename, "file"},
        {Msg, "msg"}
    };

    return mapping;
}


/**
 * @brief Override
 */
int LogModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_logLines.size();
}


/**
 * @brief Override
 *
 */
QVariant LogModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(auto row = index.row(); role)
    {
        case Timestamp:
        // Return data as QString and not as ISODateWithMs to keep nanosecs precision
        // return QDateTime::fromString(m_logLines[row].at(0), Qt::ISODateWithMs);
            return m_logLines[row].at(0); break;
        case Filename:
            return m_logLines[row].at(1); break;
        case Msg:
            return m_logLines[row].at(2); break;
        default:
            qDebug() << "Error: no valid role";
    }

    return QVariant();
}


/**
 * @brief The data insertion func for LogModel
 * @param line follows the following template { timestamp, filename, logmessage }
 *
 */
void LogModel::insertLogLine(const QStringList line)
{
    const int newRow = m_logLines.size();

    beginInsertRows(QModelIndex(),newRow,newRow);
        m_logLines.push_back(line);
    endInsertRows();
}


/**
 * @brief Fill the model from the log files
 *
 */
void LogModel::populate(const QStringList &filesToCombine)
{
    for(const auto& path : filesToCombine)
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
                    // Code to filter out log messages which should never be inserted in the model at the first place (decoration,etc)
                    if ( std::any_of(filters.begin(), filters.end(),
                                     [&logMessage](const auto& filter){ return QRegularExpression(filter).match(logMessage).hasMatch(); }))
                        continue;
                    */

                    insertLogLine( { timestamp, " [" + baseLogName.leftJustified(10, ' ', true) + "] ", logMessage });
                }
            }
        }
    }
}

