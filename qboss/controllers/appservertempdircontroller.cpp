#include "appservertempdircontroller.h"
#include "appservercontroller.h"

AppServerTempDirController::AppServerTempDirController(QObject *parent) : AppServerControllerBase(parent)
{

}
bool AppServerTempDirController::ok()
{
   if(!this->m_bAktive)return false;
   if(!this->m_pAppServerController->isOK())
       return false;
   QString sTempDir = this->GetTempDir();
   if(str::isempty(sTempDir))
       return false;
   return true;
}
QString AppServerTempDirController::GetTempDir()
{
    QString sDir(str::getDir(this->m_pAppServerController->GetAppServerStartScript()));
    if(f::exists(str::makeAbsFN(sDir, "temp")))
        return str::makeAbsFN(sDir, "temp");
    sDir = str::getDir(sDir);
    if(f::exists(str::makeAbsFN(sDir, "temp")))
        return str::makeAbsFN(sDir, "temp");
    {
        //ojje, ojje: invalid appserver path?
    }
    return QString::null;
}
