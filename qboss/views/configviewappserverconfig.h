#ifndef CONFIGVIEWAPPSERVERCONFIG_H
#define CONFIGVIEWAPPSERVERCONFIG_H

#include <QWidget>
#include <QListWidgetItem>
#include "configview.h"
#include "controllers/appserverconfigcontroller.h"

class ConfigViewAppServerConfig : public ConfigView
{
    Q_OBJECT
public:
    ConfigViewAppServerConfig(QWidget *parent = nullptr);
public:
    virtual AppServerControllerBase* getController(AppServerControllers* appServerControllers, logger* pLogger, Ui::TabSettings *ui, AppServerController* pAppServerController);
protected:
    AppServerConfigController* m_pAppServerConfigController;
    void setok();
private slots:
    void on_jbossconfigfiles_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_jbossconfigfiles_chk_toggled(bool checked);

};

#endif // CONFIGVIEWAPPSERVERCONFIG_H
