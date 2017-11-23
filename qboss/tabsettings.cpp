#include "tabsettings.h"
#include "ui_tabsettings.h"
#include "util/str.h"
#include "util/w.h"
#include <QMessageBox>

TabSettings::TabSettings(QWidget *parent) :
    QWidget(parent),
    m_appServerSettings(this),
    ui(new Ui::TabSettings),
    m_pLogger(nullptr)
{
    ui->setupUi(this);
    QObjectList children = this->children();
    activateAnis(children);
    this->installEventFilter(this);
}

void TabSettings::init(logger* pLogger)
{
    this->m_pLogger = pLogger;
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
    }
    if(recDepth > 13)
    {
        this->m_pLogger->err("onDeactivate 13!");
        return;
    }
    //m_pLogger->inf("onCfg recDepth:"+QString::number(recDepth)+" children:"+QString::number(children.length()));
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

}

void TabSettings::on_stopB_clicked()
{

}

void TabSettings::on_restartB_clicked()
{

}

void TabSettings::on_jbossstartscript_edit_textChanged(const QString &sAppServerStartScript)
{
    //TODO: set icon & buttons
    bool bAppServerStartScriptIsValid = m_appServerSettings.setAppServerStartScript(sAppServerStartScript);
    this->ui->jbossstartscript_ok_label->setAniState(bAppServerStartScriptIsValid ? anioklabel::OK : anioklabel::NOK);
}

void TabSettings::on_jbossstartscript_browse_clicked()
{
    QString sAppServerBat(w::getOpenFileName(this, "choose the App Server Start Script", "*.bat"));
    if(str::isempty(sAppServerBat))return;
    this->ui->jbossstartscript_edit->setText(sAppServerBat);
}
