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
    virtual bool ok();
protected:
    QString m_sWarAbsFN2Deploy;
};

#endif // APPSERVERDEPLOYCONTROLLER_H
