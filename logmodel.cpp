#include <QDateTime>

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

    int row = index.row();

    if (role == Timestamp)
        // Return data as QString and not as ISODateWithMs to keep nanosecs precision
        // return QDateTime::fromString(m_logLines[row].at(0), Qt::ISODateWithMs);
        return m_logLines[row].at(0);

    else if (role == Filename)
            return m_logLines[row].at(1);

    else if (role == Msg)
            return m_logLines[row].at(2);

    qDebug() << "Error: no valid role";
    return QVariant();
}


/**
 * @brief The data insertion func for LogModel
 * @param line follows the following template { timestamp, filename, logmessage }
 *
 */
void LogModel::insertLogLine(QStringList line)
{
    const int newRow = m_logLines.size();

    beginInsertRows(QModelIndex(),newRow,newRow);
        m_logLines.push_back(line);
    endInsertRows();

}
