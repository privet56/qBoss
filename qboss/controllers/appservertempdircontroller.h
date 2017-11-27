#ifndef APPSERVERTEMPDIRCONTROLLER_H
#define APPSERVERTEMPDIRCONTROLLER_H

#include <QObject>
#include "appservercontrollerbase.h"

class AppServerTempDirController : public AppServerControllerBase
{
    Q_OBJECT
public:
    AppServerTempDirController(QObject *parent = nullptr);
public:
    virtual bool ok();
    QString GetTempDir();
};

#endif // APPSERVERTEMPDIRCONTROLLER_H
