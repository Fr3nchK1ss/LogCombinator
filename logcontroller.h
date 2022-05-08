#pragma once

#include <QObject>
#include <QRegularExpression>

#include "logmodel.h"


/**
 * @brief The LogController class
 *
 * The LogController is the bridge between the QML UI and the logmodel
 */
class LogController : public QObject
{
    Q_OBJECT
    static const inline QString m_compoundedLogPath{"compounded.log"};
    QStringList m_filesToCombine;

public slots:
    void registerLogFile(const QString logFile, bool isChecked);
    void combineFiles();

};
