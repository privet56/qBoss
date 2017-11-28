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
    this->m_pAppServerTempDirController->setActive(checked);
    setok();
}
void ConfigViewTempDirView::setok()
{
    //this->m_pLogger->inf("appserverc.ok:"+QString::number(this->m_pAppServerController->isOK())+" tempdircontroller:active:"+QString::number(this->m_pAppServerTempDirController->active())+" tempdircontroller:ok:"+QString::number(this->m_pAppServerTempDirController->ok()));

    if(!this->m_pAppServerTempDirController->active())
    {
        this->ui->jbosstempcleanup_ok_label->setAniState(anioklabel::OkState::INACTIVE);
        return;
    }

    this->ui->jbosstempcleanup_ok_label->setAniState(this->m_pAppServerTempDirController->ok() ? anioklabel::OkState::OK : anioklabel::OkState::NOK);
}
