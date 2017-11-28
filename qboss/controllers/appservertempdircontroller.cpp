#include "appservertempdircontroller.h"
#include "appservercontroller.h"

AppServerTempDirController::AppServerTempDirController(QObject *parent) : AppServerControllerBase(parent)
{

}
bool AppServerTempDirController::ok()
{
   if(!this->active())return true;
   //if(!this->m_pAppServerController->isOK()) return false;
   {
       QString sTempDir = this->GetTempDir();
       if(str::isempty(sTempDir))
           return false;
   }
   {
       QString sLogDir = this->GetLogDir();
       if(str::isempty(sLogDir))
           return false;
   }
   return true;
}
QString AppServerTempDirController::GetTempDir()
{
    return this->GetSubDir("temp");
}
QString AppServerTempDirController::GetLogDir()
{
    return this->GetSubDir("logs");
}

bool AppServerTempDirController::action()
{
    if(!this->active())return true;
    QString sAppServerTempDir = this->GetTempDir();
    QString sAppServerLogDir  = this->GetLogDir();
    {
        if(str::isempty(sAppServerTempDir) || !f::exists(sAppServerTempDir))
        {
            this->m_pLogger->err("cannot access app server temp dir '"+sAppServerTempDir+"'");
            return false;
        }
        if(!f::emptydir(sAppServerTempDir, this->m_pLogger))
        {
            this->m_pLogger->err("cannot cleanup app server temp dir '"+sAppServerTempDir+"'");
            return false;
        }
    }
    {
        if(str::isempty(sAppServerLogDir) || !f::exists(sAppServerLogDir))
        {
            this->m_pLogger->err("cannot access app server Log dir '"+sAppServerLogDir+"'");
            return false;
        }
        if(!f::emptydir(sAppServerLogDir, this->m_pLogger))
        {
            this->m_pLogger->err("cannot cleanup app server Log dir '"+sAppServerLogDir+"'");
            return false;
        }
    }
    this->m_pLogger->inf("cleaned up '"+sAppServerLogDir+"' & '"+sAppServerTempDir+"'");
    return true;
}
