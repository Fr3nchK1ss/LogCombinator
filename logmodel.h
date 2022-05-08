#pragma once

#include <QAbstractListModel>
#include <QRegularExpressionMatch>
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
    std::vector<QStringList> m_logLines;

    // rxLogLine matches following entries
    //   (YYYY-MM-DDTHH::MM::ss.mmmnnn)(message)
    static const inline QRegularExpression m_rxLogLine{"(^.{0,10}T{0,1}\\d{2}:\\d{2}:\\d{2}\\.\\d{6})(.*)"};

    void insertLogLine(const QStringList line);

public:
    enum LogRoles {
        Timestamp = Qt::UserRole,
        Filename,
        Msg
    };

    LogModel(QObject *parent = nullptr): QAbstractListModel(parent){}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void populate(const QStringList& filesToCombine);
};
