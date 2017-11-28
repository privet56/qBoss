#include "configviewappserverconfig.h"
#include "ui_tabsettings.h"

ConfigViewAppServerConfig::ConfigViewAppServerConfig(QWidget *parent) : ConfigView(parent), m_pAppServerConfigController(nullptr)
{

}
AppServerControllerBase* ConfigViewAppServerConfig::getController(AppServerControllers* appServerControllers, logger* pLogger, Ui::TabSettings *ui, AppServerController* pAppServerController)
{
    ConfigView::getController(appServerControllers, pLogger, ui, pAppServerController);
    {
        connect(ui->jbossconfigfiles_list, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(on_jbossconfigfiles_list_currentItemChanged(QListWidgetItem*, QListWidgetItem*)));
        connect(ui->jbossconfigfiles_chk , SIGNAL(toggled(bool)), this, SLOT(on_jbossconfigfiles_chk_toggled(bool)));
    }
    m_pAppServerConfigController = new AppServerConfigController(appServerControllers);
    m_pAppServerConfigController->init(pLogger, pAppServerController);
    return m_pAppServerConfigController;
}
void ConfigViewAppServerConfig::on_jbossconfigfiles_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(current)
    Q_UNUSED(previous)

    QListWidget* pSender = dynamic_cast<QListWidget*>(sender());
    this->m_pAppServerConfigController->setActiveConfigFileIndex(pSender->currentRow());
    setok();
}
void ConfigViewAppServerConfig::on_jbossconfigfiles_chk_toggled(bool checked)
{
    this->m_pAppServerConfigController->setActive(checked);
    setok();
}
void ConfigViewAppServerConfig::setok()
{
    if(!this->m_pAppServerConfigController->active())
    {
        this->ui->jbossconfigfiles_ok_label->setAniState(anioklabel::OkState::INACTIVE);
    }
    else
    {
        this->ui->jbossconfigfiles_ok_label->setAniState(this->m_pAppServerConfigController->ok() ? anioklabel::OkState::OK : anioklabel::OkState::NOK);
    }
}
