#include "appservercontroller.h"
#include "util/f.h"

AppServerController::AppServerController(QObject *parent) : QObject(parent)
{

}

bool AppServerController::setAppServerStartScript(QString sAppServerStartScript)
{
    this->m_sAppServerStartScript = sAppServerStartScript;
    QFile f(sAppServerStartScript);
    return f.exists();
}
