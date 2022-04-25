#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H

#include <QObject>

#include "logmodel.h"


/**
 * @brief The LogController class
 *
 * The LogController bridges between the QML UI and the log model
 */
class LogController : public QObject
{
    Q_OBJECT

    QStringList m_filesToCombine;
    void populateModel(LogModel &model);

public slots:
    void registerLogFile(QString logFile, bool isChecked);
    void combineFiles();


};

#endif // LOGCONTROLLER_H
