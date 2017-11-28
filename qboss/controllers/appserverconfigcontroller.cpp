#include "appserverconfigcontroller.h"

AppServerConfigController::AppServerConfigController(QObject *parent) : AppServerControllerBase(parent), m_iConfigFile2Set(-1)
{

}
void AppServerConfigController::setActiveConfigFileIndex(int iConfigFile2Set)
{
    this->m_iConfigFile2Set = iConfigFile2Set;
}
bool AppServerConfigController::ok()
{
    if(!this->active())
        return true;
    if(this->m_iConfigFile2Set < 0)
        return false;
    return true;
}
bool AppServerConfigController::action()
{
    if(!this->active())return true;
    //TODO:
    return true;
}
