#include <QThread>
#include "appservercontroller.h"
#include "util/f.h"
#include "util/str.h"

AppServerController::AppServerController(QObject *parent) : QObject(parent), m_pProcess(nullptr), m_pLogger(nullptr), m_appServerControllers(this)
{

}
void AppServerController::init(logger* pLogger)
{
    this->m_pLogger = pLogger;
    this->m_appServerControllers.init(pLogger);
}
AppServerControllers* AppServerController::getSubControllers()
{
    return &this->m_appServerControllers;
}
QString AppServerController::GetAppServerStartScript()
{
    return this->m_sAppServerStartScript;
}
void AppServerController::addSubController(AppServerControllerBase* appServerControllerBase)
{
    this->m_appServerControllers.add(appServerControllerBase);
}
bool AppServerController::setAppServerStartScript(QString sAppServerStartScript)
{
    this->m_sAppServerStartScript = sAppServerStartScript;
    this->getSubControllers()->setok();
    return this->isOK(true);
}
bool AppServerController::isOK(bool bOnlyMyOK)
{
    if(!f::exists(this->m_sAppServerStartScript))
        return false;
    if(bOnlyMyOK)return true;
    return this->getSubControllers()->ok();
}
bool AppServerController::running()
{
    return this->m_pProcess != nullptr;
}
bool AppServerController::start()
{
    if(!this->isOK(false))
    {
        this->m_pLogger->wrn("cannot start! fnf:'"+this->m_sAppServerStartScript+"'");
        return false;
    }
    if(this->running())
    {
        this->m_pLogger->wrn("cannot start! already running:"+this->m_sAppServerStartScript);
        return false;
    }

    this->getSubControllers()->action();

    this->m_pProcess = new QProcess(this);
    this->m_pProcess->setWorkingDirectory(str::getDir(this->m_sAppServerStartScript));

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QStringList sysEnv = QProcess::systemEnvironment();
    env.insert("JAVA_HOME", "");    //TODO: check if necessary!
    //this->m_pProcess->setProcessEnvironment(env);
    QStringList arguments;

    //this->m_pProcess->setProcessChannelMode(QProcess::MergedChannels);  //it will cause printing everything (even stderr output) to stdout output
    //this->m_pProcess->setInputChannelMode(QProcess::ForwardedInputChannel);
    //this->m_pProcess->setStandardOutputFile("std.txt");
    //connect(this->m_pProcess,   SIGNAL(readyRead()), this, SLOT(onProcessReadyReadAll()));
    connect(this->m_pProcess,   SIGNAL(readyReadStandardOutput()), this, SLOT(onProcessReadyReadStdOutput()));
    connect(this->m_pProcess,   SIGNAL(readyReadStandardError()) , this, SLOT(onProcessReadyReadStdErr()));
    connect(this->m_pProcess,   SIGNAL(started()), this, SLOT(onProcessStarted()));
    connect(this->m_pProcess,   SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onProcessFinished(int,QProcess::ExitStatus)));
    this->m_pProcess->setObjectName(m_sAppServerStartScript);
    this->m_pProcess->start(this->m_sAppServerStartScript, arguments);
    //int iProcessStarted = this->m_pProcess->execute(this->m_sAppServerStartScript, arguments); //if the process cannot be started, -2 is returned
    return true;
}
void AppServerController::onProcessStarted()
{
    //QProcess* p = (QProcess*)sender();
    //QProcess::ProcessError err = p->error();
    //this->m_pLogger->inf("Process started("+QString::number(err)+")!");
    emit processStarted();
}
void AppServerController::onProcessReadyReadStdOutput()
{
    QProcess* p = (QProcess*)sender();
    QString s = p->readAllStandardOutput();
    s = s.trimmed();
    this->m_pLogger->inf(logger::PREFIX_STDOUT+s);
}
void AppServerController::onProcessReadyReadStdErr()
{
    QProcess* p = (QProcess*)sender();
    QString s = p->readAllStandardError();
    s = s.trimmed();
    this->m_pLogger->err(logger::PREFIX_STDERR+s);
}
void AppServerController::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    //QProcess* p = (QProcess*)sender();
    //this->m_pLogger->wrn("onProcessFinished: process finished: "+QString::number(exitCode)+" exitStatus:"+QString::number(exitStatus));
    this->stop(exitCode, exitStatus);
}
bool AppServerController::stop(int exitCode, QProcess::ExitStatus exitStatus)
{
    if(!this->running())
    {
        this->m_pLogger->wrn("cannot stop (as not running)");
        return false;
    }
    qint64 pid = this->m_pProcess->processId();
    w::killSubProcesses(pid, this->m_pLogger);
    this->m_pProcess->disconnect();
    this->m_pProcess->terminate();
    QThread::msleep(300);
    this->m_pProcess->close();
    QThread::msleep(300);
    if (this->m_pProcess->state() != QProcess::NotRunning)
    {
        this->m_pProcess->kill();
        QThread::msleep(300);
    }
    this->m_pProcess->deleteLater();
    delete this->m_pProcess;
    this->m_pProcess = nullptr;
    //this->m_pLogger->wrn("stop: process finished: "+QString::number(exitCode)+" exitStatus:"+QString::number(exitStatus));
    emit processFinished(exitCode, exitStatus);
    return true;
}
bool AppServerController::restart()
{
    if(!this->running())
    {
        this->m_pLogger->wrn("cannot restart (as not running)");
        return false;
    }
    if(!this->isOK(false))
    {
        this->m_pLogger->wrn("cannot restart (as not OK)");
        return false;
    }
    this->stop();
    return this->start();
}
