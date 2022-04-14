#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H

#include <QObject>
#include <QFileSystemModel>

#include "logmodel.h"


/**
 * @brief The LogController class
 *
 * The LogController bridges between the QML UI and the log model
 */
class LogController : public QObject
{
    Q_OBJECT

    LogModel logModel;
    QStringList filesToCombine;

public:
    LogController(QObject *parent = nullptr);

public slots:
    void registerLogFile(QString logFile, bool isChecked);

};

#endif // LOGCONTROLLER_H
