#include "appserverdeploycontroller.h"
#include "util/f.h"
#include "util/str.h"
#include <QDir>
#include <QRegExp>
#include <QStringList>
#include <QFileInfo>

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
bool AppServerDeployController::cleanupDeployedWarDir(QString sAbsFNDeployedWar)
{
    QString sWebAppsDir = str::getDir(sAbsFNDeployedWar);
    QString sWarFN = str::getFN(sAbsFNDeployedWar);
    QRegExp firstW("\\W");
    int pos = firstW.indexIn(sWarFN);

    if( pos < 0)
    {
        this->m_pLogger->err("cannot cleanup dir of invalid war fn:'"+sAbsFNDeployedWar+"'");
        return false;
    }

    //works for tomee   //TODO: check for jboss

    QString dFirstWord = sWarFN.left(pos);
    {
        QDir d(sWebAppsDir);
        d.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
        QStringList filters;
        filters << dFirstWord+"*";
        d.setNameFilters(filters);
        QStringList fs = d.entryList();

        for(int i=0; i < fs.length(); i++)
        {
            QString sUnpackedWarDir(str::makeAbsFN(sWebAppsDir,fs.at(i)));
            QFileInfo fi(sUnpackedWarDir);
            if(fi.isDir())
            {
                QDir subdir(sUnpackedWarDir);
                if(!f::emptydir(sUnpackedWarDir, this->m_pLogger) || !subdir.removeRecursively())
                {
                    this->m_pLogger->err("cannot cleanup sUnpackedWarDir:'"+sUnpackedWarDir+"'");
                    return false;
                }
                this->m_pLogger->inf("cleanup OK sUnpackedWarDir:'"+sUnpackedWarDir+"'");
            }
            else
            {
                this->m_pLogger->err("sUnpackedWarDir is no dir? '"+sUnpackedWarDir+"'");
                return false;
            }
        }
    }
    return true;
}
bool AppServerDeployController::action()
{
    if(!this->active())return true;

    QString sDirTarget  = this->getAppServerWebAppsDir();
    QString sFN         = str::getFN(this->m_sWarAbsFN2Deploy);
    QString sAbsFNTarget= str::makeAbsFN(sDirTarget, sFN);

    bool bCleanupOK = cleanupDeployedWarDir(sAbsFNTarget);
    if( !bCleanupOK)
    {
        //this->m_pLogger->err("...");  //cleanupDeployedWarDir(...) already logged...
        return false;
    }

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
