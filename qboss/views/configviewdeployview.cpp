#include "configviewdeployview.h"
#include "ui_tabsettings.h"

ConfigViewDeployView::ConfigViewDeployView(QWidget *parent) : ConfigView(parent)
{

}
AppServerControllerBase* ConfigViewDeployView::getController(AppServerControllers* appServerControllers, logger* pLogger, Ui::TabSettings *ui, AppServerController* pAppServerController)
{
    ConfigView::getController(appServerControllers, pLogger, ui, pAppServerController);
    {
        connect(ui->jbossdeploywar_watch_chk, SIGNAL(toggled(bool)), this, SLOT(on_jbossdeploywar_watch_chk_toggled(bool)));
        connect(ui->jbossdeploywar_browse, SIGNAL(clicked()), this, SLOT(on_jbossdeploywar_browse_clicked()));
        connect(ui->jbossdeploywar_edit, SIGNAL(textChanged(const QString &)), this, SLOT(on_jbossdeploywar_edit_textChanged(const QString &)));
    }
    m_pAppServerDeployController = new AppServerDeployController(appServerControllers);
    m_pAppServerDeployController->init(pLogger, pAppServerController);
    return m_pAppServerDeployController;
}
void ConfigViewDeployView::on_jbossdeploywar_watch_chk_toggled(bool checked)
{

}
void ConfigViewDeployView::on_jbossdeploywar_browse_clicked()
{
    QString sWarAbsFN(w::getOpenFileName(this, "Choose WAR/EAR/JAR/SAR file to deploy", "*.war;*.ear;*.jar;*.sar"));
    if(str::isempty(sWarAbsFN))return;
    this->ui->jbossdeploywar_edit->setText(sWarAbsFN);
}
void ConfigViewDeployView::on_jbossdeploywar_edit_textChanged(const QString &arg1)
{
    this->m_pAppServerDeployController->setWarAbsFN2Deploy(arg1);
    {

    }
}
