#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H

#include <QObject>
#include <QRegularExpression>

#include "logmodel.h"


/**
 * @brief The LogController class
 *
 * The LogController bridges between the QML UI and the log model
 */
class LogController : public QObject
{
    Q_OBJECT

    // rxLogLine matches following entries
    //   (YYYY-MM-DDT)(HH::MM::ss.mmmnnn)(message)
    //   ()(HH::MM::ss.mmmnnn)(message)
    static const inline QRegularExpression m_rxLogLine{"(^.{0,10}T{0,1})(\\d{2}:\\d{2}:\\d{2}\\.\\d{6})(.*)"};
    static const inline QString m_compoundedLogPath{"compounded.log"};

    QStringList m_filesToCombine;
    void populateModel(LogModel &model);
    void writeCompoundedLog(const LogModel& logModel);

public slots:
    void registerLogFile(QString logFile, bool isChecked);
    void combineFiles();


};

#endif // LOGCONTROLLER_H
