#ifndef CONFIGVIEW_H
#define CONFIGVIEW_H

#include <QWidget>
#include "util/cfg.h"
#include "util/logger.h"
#include "controllers/appservercontrollerbase.h"
#include "controllers/appservercontrollers.h"
#include "tabsettings.h"
#include "util/w.h"
#include "util/f.h"
#include "util/str.h"
#include "controllers/appservercontroller.h"

class ConfigView : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigView(QWidget *parent = nullptr);

public:
    virtual void init(logger* pLogger);
    virtual AppServerControllerBase* getController(AppServerControllers* appServerControllers, logger* pLogger, Ui::TabSettings *ui, AppServerController* pAppServerController);

protected:
    logger* m_pLogger;
    Ui::TabSettings *ui;
    AppServerController* m_pAppServerController;

signals:

public slots:
};

#endif // CONFIGVIEW_H
