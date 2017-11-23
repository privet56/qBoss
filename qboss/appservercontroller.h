#ifndef APPSERVERCONTROLLER_H
#define APPSERVERCONTROLLER_H

#include <QObject>
#include <QProcess>
#include "util/cfg.h"
#include "util/logger.h"

class AppServerController : public QObject
{
    Q_OBJECT
public:
    explicit AppServerController(QObject *parent = nullptr);
public:
    void init(logger* pLogger);
    bool setAppServerStartScript(QString sAppServerStartScript);
    bool running();
    bool isOK();
    bool start();
    bool stop();
    bool restart();

protected:
    QString m_sAppServerStartScript;
    QProcess* m_pProcess;
    logger* m_pLogger;

protected slots:
    void onProcessStarted();
    void onProcessReadyReadStdOutput();
    void onProcessReadyReadStdErr();
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);


signals:

public slots:
};

#endif // APPSERVERCONTROLLER_H
