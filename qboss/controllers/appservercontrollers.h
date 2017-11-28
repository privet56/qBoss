#ifndef APPSERVERCONTROLLERS_H
#define APPSERVERCONTROLLERS_H

#include <QObject>
#include "appservercontrollerbase.h"
#include "util/logger.h"

class AppServerControllers : public AppServerControllerBase
{
    Q_OBJECT
public:
    explicit AppServerControllers(QObject *parent = nullptr);

public:
    void init(logger* pLogger);
    void add(AppServerControllerBase* appServerController);
    int size();
    virtual bool ok();
    virtual bool action();
    virtual void setok();
protected:
    QList<AppServerControllerBase*> m_AppServerControllers;
    logger* m_pLogger;
signals:

public slots:
};

#endif // APPSERVERCONTROLLERS_H
