#include "appservercontrollerbase.h"

AppServerControllerBase::AppServerControllerBase(QObject *parent) : QObject(parent), m_pLogger(nullptr), m_bAktive(false), m_pAppServerController(nullptr)
{

}
void AppServerControllerBase::init(logger* pLogger, AppServerController* pAppServerController)
{
    this->m_pLogger = pLogger;
    this->m_pAppServerController = pAppServerController;
}
void AppServerControllerBase::setActive(bool active)
{
    this->m_bAktive = active;
}
bool AppServerControllerBase::ok()
{
    return false;
}
bool AppServerControllerBase::active()
{
    return this->m_bAktive;
}
