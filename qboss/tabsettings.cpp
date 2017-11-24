#include "tabsettings.h"
#include "ui_tabsettings.h"
#include "util/str.h"
#include "util/w.h"
#include <QMessageBox>
#include <QRadioButton>

TabSettings::TabSettings(QWidget *parent) :
    QWidget(parent),
    m_appServerSettings(this),
    ui(new Ui::TabSettings),
    m_pLogger(nullptr)
{
    ui->setupUi(this);
    this->ui->stopB->setEnabled(false);
    this->ui->restartB->setEnabled(false);
    QObjectList children = this->children();
    activateAnis(children);
    this->installEventFilter(this);
    connect(&this->m_appServerSettings,SIGNAL(processFinished(int,QProcess::ExitStatus)), this, SLOT(onProcessFinished(int,QProcess::ExitStatus)));
    connect(&this->m_appServerSettings,SIGNAL(processStarted()), this, SLOT(onProcessStarted()));
}

void TabSettings::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    //Q_UNUSED(exitCode);
    //Q_UNUSED(exitStatus);
    bool bSettingsOK = this->m_appServerSettings.isOK();
    this->ui->startB->setEnabled(bSettingsOK);
    this->ui->stopB->setEnabled(false);
    this->ui->restartB->setEnabled(false);
    this->m_pLogger->log("Process finished exitCode:"+QString::number(exitCode)+" exitStatus:"+QString(exitStatus), exitCode == 0 ? logger::LogLevel::INF : logger::LogLevel::ERR);
    this->ui->appServerStatusLabel->setani("res/bunny_sleep.gif");
}

void TabSettings::onProcessStarted()
{
    this->ui->startB->setEnabled(false);
    this->ui->stopB->setEnabled(true);
    this->ui->restartB->setEnabled(this->m_appServerSettings.isOK());
    this->m_pLogger->inf("Process started.");
    this->ui->appServerStatusLabel->setani("res/bunny_run.gif");
}

void TabSettings::init(logger* pLogger)
{
    this->m_pLogger = pLogger;
    m_appServerSettings.init(pLogger);
    {
        QObjectList children = this->children();
        onCfg(children, 0, true);
    }
}
bool TabSettings::eventFilter(QObject* obj, QEvent* event)
{
    //events when closing the app:
        //25: QEvent::WindowDeactivate      //occurs when closing the main app
        //18: QEvent::Hide                  //occurs also when changing the tabs...

    //if(this->m_pLogger &&   (event->type() != QEvent::Paint/*12*/) &&
    //                        (event->type() != QEvent::LayoutRequest/*76*/) &&
    //                        (event->type() != QEvent::Leave/*11*/) &&
    //                        (event->type() != QEvent::Move/*13*/) &&
    //                        (event->type() != QEvent::Resize/*14*/)
    //   )
    //{
    //    m_pLogger->inf("event:"+QString::number(event->type()));
    //}
    if(event->type() == QEvent::WindowDeactivate)
    {
        QObjectList children = this->children();
        onCfg(children, 0, false);
    }
    return QWidget::eventFilter(obj,event);
}
void TabSettings::onCfg(QObjectList& children, int recDepth, bool bRead)
{
    if(!this->m_pLogger || !this->m_pLogger->GetCfg())
    {
        this->m_pLogger->err("in onDeactivate");
        return;
    }//m_pLogger->inf("onCfg recDepth:"+QString::number(recDepth)+" children:"+QString::number(children.length()));
    if(recDepth > 13)
    {
        this->m_pLogger->err("onDeactivate 13!");
        return;
    }
    for(int i=0;i<children.length();i++)
    {
        QObject* pChild = children.at(i);
        if(dynamic_cast<QWidget*>(pChild))
        {
            if(dynamic_cast<QLineEdit*>(pChild))
            {
                if(bRead)
                {
                    QString s(this->m_pLogger->GetCfg()->getValue(pChild->objectName()));
                    if(!str::isempty(s, false))
                        dynamic_cast<QLineEdit*>(pChild)->setText(s);
                }
                else
                    this->m_pLogger->GetCfg()->setValue(pChild->objectName(), dynamic_cast<QLineEdit*>(pChild)->text());
            }
            else if(dynamic_cast<QCheckBox*>(pChild))
            {
                if(bRead)
                {
                    QString s(this->m_pLogger->GetCfg()->getValue(pChild->objectName()));
                    if(!str::isempty(s, true))
                        dynamic_cast<QCheckBox*>(pChild)->setChecked(s == "1");
                }
                else
                    this->m_pLogger->GetCfg()->setValue(pChild->objectName(), QString::number(dynamic_cast<QCheckBox*>(pChild)->isChecked()));
            }
            else if(dynamic_cast<QListWidget*>(pChild))
            {
                if(bRead)
                {
                    QString s(this->m_pLogger->GetCfg()->getValue(pChild->objectName()));
                    if(!str::isempty(s, true))
                        dynamic_cast<QListWidget*>(pChild)->setCurrentRow(s.toInt());
                }
                else
                    this->m_pLogger->GetCfg()->setValue(pChild->objectName(), QString::number(dynamic_cast<QListWidget*>(pChild)->currentRow()));
            }
            else if(dynamic_cast<QRadioButton*>(pChild) ||
                    dynamic_cast<QTextEdit*>(pChild))   //and time,date,spin,slider,scrollbar,combo...
            {
                this->m_pLogger->err("save/load for this item is not implemented ("+pChild->objectName()+")");
            }
        }
        QObjectList childChildren = pChild->children();
        this->onCfg(childChildren, recDepth+1, bRead);
    }
}

void TabSettings::activateAnis(QObjectList& children)
{
    for(int i=0;i<children.length();i++)
    {
        QObject* pChild = children.at(i);
        {
            anilabel* pAniLabel = dynamic_cast<anilabel*>(pChild);
            if( pAniLabel && !str::isempty(pAniLabel->toolTip()))
            {
                pAniLabel->setani(":/res/"+pAniLabel->toolTip()+".gif");
            }
        }
        QObjectList childChildren = pChild->children();
        this->activateAnis(childChildren);
    }
}

TabSettings::~TabSettings()
{
    delete ui;
}

void TabSettings::on_startB_clicked()
{
    m_appServerSettings.start();
}

void TabSettings::on_stopB_clicked()
{
    m_appServerSettings.stop();
}

void TabSettings::on_restartB_clicked()
{
    m_appServerSettings.restart();
}

void TabSettings::on_jbossstartscript_edit_textChanged(const QString &sAppServerStartScript)
{
    bool bSettingsOK = m_appServerSettings.setAppServerStartScript(sAppServerStartScript);
    this->ui->jbossstartscript_ok_label->setAniState(bSettingsOK ? anioklabel::OK : anioklabel::NOK);
    this->ui->jbosstempcleanup_area->setEnabled(bSettingsOK);
    this->ui->jbossdeploywar_area->setEnabled(bSettingsOK);
    this->ui->jbossconfigfiles_area->setEnabled(bSettingsOK);
    this->ui->startB->setEnabled(bSettingsOK && !this->m_appServerSettings.running());
}

void TabSettings::on_jbossstartscript_browse_clicked()
{
    QString sAppServerBat(w::getOpenFileName(this, "choose the App Server Start Script", "*.bat"));
    if(str::isempty(sAppServerBat))return;
    this->ui->jbossstartscript_edit->setText(sAppServerBat);
}
