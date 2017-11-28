#include "appserverdeploycontroller.h"

AppServerDeployController::AppServerDeployController(QObject *parent) : AppServerControllerBase(parent), m_bWatch(false)
{

}
void AppServerDeployController::setWarAbsFN2Deploy(QString sWarAbsFN2Deploy)
{
    this->m_sWarAbsFN2Deploy = sWarAbsFN2Deploy;
}
bool AppServerDeployController::ok()
{
   if(!this->active())return true;

   if(!this->getWatch() && str::isempty(this->m_sWarAbsFN2Deploy))
   {
       return true;
   }

   bool bWarOK = f::exists(this->m_sWarAbsFN2Deploy);
   return bWarOK;
}
void AppServerDeployController::setWatch(bool bWatch)
{
    this->m_bWatch = bWatch;
}
QString AppServerDeployController::getWarAbsFN2Deploy()
{
    return this->m_sWarAbsFN2Deploy;
}
bool AppServerDeployController::getWatch()
{
    return this->m_bWatch;
}
bool AppServerDeployController::active()
{
    this->setActive(!str::isempty(getWarAbsFN2Deploy()));
    return this->m_bActive;
}
bool AppServerDeployController::action()
{
    if(!this->active())return true;

    QString sDirTarget  = this->getAppServerWebAppsDir();
    QString sFN         = str::getFN(this->m_sWarAbsFN2Deploy);
    QString sAbsFNTarget= str::makeAbsFN(sDirTarget, sFN);
    QFile::remove(sAbsFNTarget);
    if(!QFile::copy(this->getWarAbsFN2Deploy(), sAbsFNTarget))
    {
        this->m_pLogger->err("cannot copy\n\t'"+this->getWarAbsFN2Deploy()+"'\n\t'"+sAbsFNTarget+"'");
        return false;
    }
    this->m_pLogger->inf("copy ok:'"+this->getWarAbsFN2Deploy()+"'->'"+sAbsFNTarget+"'");
    return true;
}
QString AppServerDeployController::getAppServerWebAppsDir()
{
    return this->GetSubDir("webapps");
}
