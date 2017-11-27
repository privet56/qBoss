#include "appservercontrollers.h"

AppServerControllers::AppServerControllers(QObject *parent) : AppServerControllerBase(parent), m_pLogger(nullptr)
{

}
void AppServerControllers::add(AppServerControllerBase* appServerController)
{
    if(appServerController == nullptr)
        this->m_pLogger->wrn("controllers::add: no appServerController2Add!");
    if(!this->m_AppServerControllers.contains(appServerController))
    {
        this->m_AppServerControllers.append(appServerController);
    }
}
int AppServerControllers::size()
{
    return this->m_AppServerControllers.size();
}
void AppServerControllers::init(logger* pLogger)
{
    this->m_pLogger = pLogger;
}
