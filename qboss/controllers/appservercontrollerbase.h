#ifndef APPSERVERCONTROLLERBASE_H
#define APPSERVERCONTROLLERBASE_H

#include <QObject>
#include "util/logger.h"
#include "util/w.h"
#include "util/f.h"
#include "util/str.h"

//#include "appservercontroller.h"
class AppServerController;

class AppServerControllerBase : public QObject
{
    Q_OBJECT
public:
    explicit AppServerControllerBase(QObject *parent = nullptr);

public:
    virtual void init(logger* pLogger, AppServerController* pAppServerController);
    virtual void setActive(bool active);
    virtual bool active();
    virtual bool ok();
    virtual bool action();
    virtual void setok();

    QString GetSubDir(QString sSubDir);

protected:
    logger* m_pLogger;
    bool m_bActive;
    AppServerController* m_pAppServerController;

signals:

public slots:
};

#endif // APPSERVERCONTROLLERBASE_H
