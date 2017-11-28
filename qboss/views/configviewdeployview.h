#ifndef CONFIGVIEWDEPLOYVIEW_H
#define CONFIGVIEWDEPLOYVIEW_H

#include <QWidget>
#include "configview.h"
#include "controllers/appserverdeploycontroller.h"

class ConfigViewDeployView : public ConfigView
{
    Q_OBJECT
public:
    ConfigViewDeployView(QWidget *parent = nullptr);
public:
    virtual AppServerControllerBase* getController(AppServerControllers* appServerControllers, logger* pLogger, Ui::TabSettings *ui, AppServerController* pAppServerController);
public:

protected:
    AppServerDeployController* m_pAppServerDeployController;
    void setok();

private slots:
    void on_jbossdeploywar_watch_chk_toggled(bool checked);
    void on_jbossdeploywar_browse_clicked();
    void on_jbossdeploywar_edit_textChanged(const QString &arg1);
};

#endif // CONFIGVIEWDEPLOYVIEW_H
