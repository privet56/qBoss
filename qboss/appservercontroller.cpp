#include "appservercontroller.h"
#include "util/f.h"
#include "util/str.h"

AppServerController::AppServerController(QObject *parent) : QObject(parent), m_pProcess(nullptr), m_pLogger(nullptr)
{

}
void AppServerController::init(logger* pLogger)
{
    this->m_pLogger = pLogger;
}
bool AppServerController::setAppServerStartScript(QString sAppServerStartScript)
{
    this->m_sAppServerStartScript = sAppServerStartScript;
    return this->isOK();
}
bool AppServerController::isOK()
{
    return f::exists(this->m_sAppServerStartScript);
}
bool AppServerController::running()
{
    return this->m_pProcess != nullptr;
}
bool AppServerController::start()
{
    if(!this->isOK())
    {
        //log!
        return false;
    }
    if(this->running())
    {
        //log!
        return false;
    }
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

    //TODO: check if getDir works correctly
    //TODO: listen for crash of the started process!
    //TODO: connect to stdout/stderr!

    return false;
}
void AppServerController::onProcessStarted()
{
    QProcess* p = (QProcess*)sender();

    //TODO: check error:
        //QProcess::ProcessError errr= p.error();
        //if(errr==QProcess::FailedToStart) qDebug("QProcess::FailedToStart");
        //if(errr==QProcess::ReadError    ) qDebug("QProcess::ReadError");
        //if(errr==QProcess::FailedToStart) qDebug("QProcess::FailedToStart");
}
void AppServerController::onProcessReadyReadStdOutput()
{
    QProcess* p = (QProcess*)sender();
    QString s = p->readAllStandardOutput();
    s = s.trimmed();
    //TODO: log!
}
void AppServerController::onProcessReadyReadStdErr()
{
    QProcess* p = (QProcess*)sender();
    QString s = p->readAllStandardError();
    s = s.trimmed();
    //TODO: log!
}
void AppServerController::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QProcess* p = (QProcess*)sender();
    //TODO://p->exitCode();
}

bool AppServerController::stop()
{
    if(this->running())
    {
        //log!
        return false;
    }

    this->m_pProcess->terminate();
    this->m_pProcess->close();
    this->m_pProcess->kill();
    this->m_pProcess->deleteLater();
    this->m_pProcess->disconnect();
    delete this->m_pProcess;
    this->m_pProcess = nullptr;
    return true;
}
bool AppServerController::restart()
{
    if(!this->running())
    {
        //log!
        return false;
    }

    return false;
}
