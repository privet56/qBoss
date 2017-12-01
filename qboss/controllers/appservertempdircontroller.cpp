#include "appservertempdircontroller.h"
#include "appservercontroller.h"

AppServerTempDirController::AppServerTempDirController(QObject *parent) : AppServerControllerBase(parent)
{

}
bool AppServerTempDirController::ok()
{
   if(!this->active())return true;

   QList<QString> lsTempDirs = this->GetTempDirs();
   for(int i=0;i< lsTempDirs.size();i++)
   {
       QString sAppServerTempDir(lsTempDirs.at(i));
       if(!str::isempty(sAppServerTempDir) && f::exists(sAppServerTempDir))
       {
           return true;//min 1 temp dir found
       }
   }
   return false;
}
QList<QString> AppServerTempDirController::GetTempDirs()
{
    QList<QString> lsTempDirs;
    lsTempDirs << this->GetSubDir("temp");
    lsTempDirs << this->GetSubDir("logs");
    lsTempDirs << this->GetSubDir("work");
    lsTempDirs << this->GetSubDir("webapps/temp");  //TODO: check dir name pattern after failed deployment!
    return lsTempDirs;
}

bool AppServerTempDirController::action()
{
    if(!this->active())return true;
    QList<QString> lsTempDirs = this->GetTempDirs();
    int iCleanedUp = 0;
    for(int i=0;i<lsTempDirs.size();i++)
    {
        QString sAppServerTempDir(lsTempDirs.at(i));
        if(str::isempty(sAppServerTempDir) || !f::exists(sAppServerTempDir))
        {
            //this->m_pLogger->wrn("cannot access app server temp dir '"+sAppServerTempDir+"'");    //this can be a normal case!
            continue;
        }
        if(!f::emptydir(sAppServerTempDir, this->m_pLogger))
        {
            this->m_pLogger->err("cannot cleanup app server temp dir '"+sAppServerTempDir+"'");
            return false;
        }
        iCleanedUp++;
        this->m_pLogger->inf("cleaned up '"+sAppServerTempDir+"'");
    }
    if(iCleanedUp > 0)
    {
        return true;
    }
    this->m_pLogger->err("cannot access app server temp dirs for '"+this->m_pAppServerController->GetAppServerStartScript()+"'");
    return false;
}
