#include "appserverdeploycontroller.h"

AppServerDeployController::AppServerDeployController(QObject *parent) : AppServerControllerBase(parent)
{

}
void AppServerDeployController::setWarAbsFN2Deploy(QString sWarAbsFN2Deploy)
{
    this->m_sWarAbsFN2Deploy = sWarAbsFN2Deploy;
}
bool AppServerDeployController::ok()
{
   if(!this->m_bAktive)return false;
   return f::exists(this->m_sWarAbsFN2Deploy);
}
