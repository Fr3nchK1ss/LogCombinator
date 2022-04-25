#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QAbstractListModel>
#include <vector>


/**
 * @brief The LogModel class
 *
 * The model data is lines from log files
 * The lines must start with an ISO timestamp formatted like yyyy-mm-ddThh:mm:ss[.mmm]
 */
class LogModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum LogRoles {
        TimestampRole = Qt::UserRole,
        FilenameRole,
        MsgRole
    };

    explicit LogModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void insertLogLine(QStringList line);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    std::vector<QStringList> m_logLines;

};

#endif // LOGMODEL_H
