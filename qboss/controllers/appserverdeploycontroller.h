#ifndef APPSERVERDEPLOYCONTROLLER_H
#define APPSERVERDEPLOYCONTROLLER_H

#include <QObject>
#include "appservercontrollerbase.h"

class AppServerDeployController : public AppServerControllerBase
{
    Q_OBJECT
public:
    AppServerDeployController(QObject *parent = nullptr);
public:
    void setWarAbsFN2Deploy(QString sWarAbsFN2Deploy);
    QString getWarAbsFN2Deploy();
    virtual bool ok();
    void setWatch(bool bWatch);
    bool getWatch();
    virtual bool active();
    virtual bool action();
protected:
    QString m_sWarAbsFN2Deploy;
    bool m_bWatch;
    QString getAppServerWebAppsDir();
    bool cleanupDeployedWarDir(QString sAbsFNDeployedWar);
};

#endif // APPSERVERDEPLOYCONTROLLER_H
