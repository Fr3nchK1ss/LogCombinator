#include "logmodel.h"

LogModel::LogModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

/**
 * @brief Override
 */
QHash<int, QByteArray> LogModel::roleNames() const
{
    QHash<int, QByteArray> mapping {
        {TimestampRole, "timestamp"},
        {FilenameRole, "file"},
        {MsgRole, "msg"}
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
 */
QVariant LogModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();

    if (role == TimestampRole)
        return m_logLines[row].at(0); // stringlist.at(0)

    else if (role == FilenameRole)
            return m_logLines[row].at(1);

    else if (role == MsgRole)
            return m_logLines[row].at(2);


    qDebug() << "Error: no valid role";
    return QVariant();
}


/**
 * @brief The data insertion func for LogModel
 * @param line has the following template:
 *        { timestamp, filename, logmessage }
 */
void LogModel::insertLogLine(QStringList line)
{
    const int newRow = m_logLines.size();

    beginInsertRows(QModelIndex(),newRow,newRow);
        m_logLines.push_back(line);
    endInsertRows();

}
