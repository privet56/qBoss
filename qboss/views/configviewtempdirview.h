#ifndef CONFIGVIEWTEMPDIRVIEW_H
#define CONFIGVIEWTEMPDIRVIEW_H

#include <QWidget>
#include "configview.h"
#include "controllers/appservertempdircontroller.h"

class ConfigViewTempDirView : public ConfigView
{
    Q_OBJECT
public:
    ConfigViewTempDirView(QWidget *parent = nullptr);

public:
    virtual AppServerControllerBase* getController(AppServerControllers* appServerControllers, logger* pLogger, Ui::TabSettings *ui, AppServerController* pAppServerController);
protected:
    AppServerTempDirController* m_pAppServerTempDirController;
    void setok();

private slots:
    void on_clearappservertempdirs_chk_toggled(bool checked);

};

#endif // CONFIGVIEWTEMPDIRVIEW_H
