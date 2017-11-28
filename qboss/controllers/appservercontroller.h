#ifndef APPSERVERCONTROLLER_H
#define APPSERVERCONTROLLER_H

#include <QObject>
#include <QProcess>
#include "util/cfg.h"
#include "util/logger.h"
#include "appservercontrollers.h"

class AppServerController : public QObject
{
    Q_OBJECT
public:
    explicit AppServerController(QObject *parent = nullptr);
public:
    void init(logger* pLogger);
    bool setAppServerStartScript(QString sAppServerStartScript);
    bool running();
    bool isOK(bool bOnlyMyOK);
    bool start();
    bool stop(int exitCode=0, QProcess::ExitStatus exitStatus=QProcess::NormalExit);
    bool restart();
    void addSubController(AppServerControllerBase* appServerControllerBase);
    AppServerControllers* getSubControllers();
    QString GetAppServerStartScript();

protected:
    AppServerControllers m_appServerControllers;
    QString m_sAppServerStartScript;
    QProcess* m_pProcess;
    logger* m_pLogger;

protected slots:
    void onProcessStarted();
    void onProcessReadyReadStdOutput();
    void onProcessReadyReadStdErr();
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);


signals:
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processStarted();

public slots:
};

#endif // APPSERVERCONTROLLER_H
