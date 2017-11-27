#include "configviewtempdirview.h"
#include "ui_tabsettings.h"

ConfigViewTempDirView::ConfigViewTempDirView(QWidget *parent) : ConfigView(parent)
{

}
AppServerControllerBase* ConfigViewTempDirView::getController(AppServerControllers* appServerControllers, logger* pLogger, Ui::TabSettings *ui, AppServerController* pAppServerController)
{
    ConfigView::getController(appServerControllers, pLogger, ui, pAppServerController);
    {
        connect(ui->clearappservertempdirs_chk, SIGNAL(toggled(bool)), this, SLOT(on_clearappservertempdirs_chk_toggled(bool)));
    }
    m_pAppServerTempDirController = new AppServerTempDirController(appServerControllers);
    m_pAppServerTempDirController->init(pLogger, pAppServerController);
    return m_pAppServerTempDirController;
}
void ConfigViewTempDirView::on_clearappservertempdirs_chk_toggled(bool checked)
{

}
