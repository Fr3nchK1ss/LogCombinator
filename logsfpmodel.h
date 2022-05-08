#pragma once

#include <QSortFilterProxyModel>


/**
 * @brief The LogSFPModel class
 *
 * Sort data from a LogModel by timestamp.
 *
 * We only need to define a sortRole, which will be LogModel::LogRoles::Timestamp. Then the default sort()
 * function can handle timestamps either as QString or QDateTime. From the Qt doc:
 * "QSortFilterProxyModel provides a generic sort() reimplementation that operates on the sortRole()
 * (Qt::DisplayRole by default) of the items and that understands several data types, including int,
 * QString, and QDateTime"
 */
class LogSFPModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit LogSFPModel(QObject *parent = nullptr);
    void writeCompoundedLog(const QStringList &filesToCombine, const QString &compoundedLogPath);

};

