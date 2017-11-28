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
    this->setActive(true);
}
bool AppServerControllers::ok()
{
    for(int i=0;i<this->m_AppServerControllers.size();i++)
    {
        if(!this->m_AppServerControllers.at(i)->active())
            continue;
        if(!this->m_AppServerControllers.at(i)->ok())
            return false;
    }
    return true;
}
void AppServerControllers::setok()
{
    for(int i=0;i<this->m_AppServerControllers.size();i++)
    {
        this->m_AppServerControllers.at(i)->setok();
    }
}
bool AppServerControllers::action()
{
    if(!this->active())return true;

    for(int i=0;i<this->m_AppServerControllers.size();i++)
    {
        if(!this->m_AppServerControllers.at(i)->active())
            continue;
        if(!this->m_AppServerControllers.at(i)->action())
        {
            return false;
        }
    }
    return true;
}
