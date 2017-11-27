#include "configview.h"
#include "tabsettings.h"
#include "ui_tabsettings.h"

ConfigView::ConfigView(QWidget *parent) : QWidget(parent), m_pLogger(nullptr), ui(nullptr), m_pAppServerController(nullptr)
{

}
void ConfigView::init(logger* pLogger)
{
    if(pLogger != nullptr)this->m_pLogger = pLogger;
}
AppServerControllerBase* ConfigView::getController(AppServerControllers* appServerControllers, logger* pLogger, Ui::TabSettings *ui, AppServerController* pAppServerController)
{
    this->init(pLogger);
    this->ui = ui;
    this->m_pAppServerController = pAppServerController;
    return nullptr;
}
