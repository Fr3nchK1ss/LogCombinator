#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QAbstractListModel>
#include <QTextStream>
#include <vector>


/**
 * @brief The LogModel class
 *
 * The model data is composed of the lines from the different log files
 * The lines must start with an ISO timestamp formatted like yyyy-mm-ddThh:mm:ss[.mmm]
 */
class LogModel : public QAbstractListModel
{
    Q_OBJECT

    enum LogRoles {
        Timestamp = Qt::UserRole,
        Filename,
        Msg
    };
    std::vector<QStringList> m_logLines;

public:
    LogModel(QObject *parent = nullptr): QAbstractListModel(parent){}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void insertLogLine(QStringList line);
    void writeOut(QTextStream& out) const;

};

#endif // LOGMODEL_H
