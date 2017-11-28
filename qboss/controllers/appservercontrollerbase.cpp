#include "appservercontrollerbase.h"
#include "appservercontroller.h"

AppServerControllerBase::AppServerControllerBase(QObject *parent) : QObject(parent), m_pLogger(nullptr), m_bActive(false), m_pAppServerController(nullptr)
{

}
void AppServerControllerBase::init(logger* pLogger, AppServerController* pAppServerController)
{
    this->m_pLogger = pLogger;
    this->m_pAppServerController = pAppServerController;
}
void AppServerControllerBase::setActive(bool active)
{
    this->m_bActive = active;
}
bool AppServerControllerBase::ok()
{
    if(!this->active())return true;
    return false;
}
void AppServerControllerBase::setok()
{

}
bool AppServerControllerBase::active()
{
    return this->m_bActive;
}
bool AppServerControllerBase::action()
{
    if(!this->active())return true;
    return false;
}
QString AppServerControllerBase::GetSubDir(QString sSubDir)
{
    QString sDir(str::getDir(this->m_pAppServerController->GetAppServerStartScript()));
    if(f::exists(str::makeAbsFN(sDir, sSubDir)))
        return str::makeAbsFN(sDir, sSubDir);
    sDir = str::getDir(sDir);
    if(f::exists(str::makeAbsFN(sDir, sSubDir)))
        return str::makeAbsFN(sDir, sSubDir);
    {
        //ojje, ojje: invalid appserver path?
    }
    return QString::null;
}
