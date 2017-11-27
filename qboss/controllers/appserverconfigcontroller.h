#ifndef APPSERVERCONFIGCONTROLLER_H
#define APPSERVERCONFIGCONTROLLER_H

#include <QObject>
#include "appservercontrollerbase.h"

class AppServerConfigController : public AppServerControllerBase
{
    Q_OBJECT
public:
    AppServerConfigController(QObject *parent = nullptr);
public:
    void setActiveConfigFileIndex(int iConfigFile2Set);
    virtual bool ok();

protected:
    int m_iConfigFile2Set;


};

#endif // APPSERVERCONFIGCONTROLLER_H
