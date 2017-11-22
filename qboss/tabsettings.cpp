#include "tabsettings.h"
#include "ui_tabsettings.h"
#include "util/str.h"

TabSettings::TabSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabSettings)
{
    ui->setupUi(this);
    QObjectList children = this->children();
    activateAnis(children);
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

void TabSettings::on_jbossstartscript_browse_pressed()
{

}

void TabSettings::on_jbossstartscript_browse_2_pressed()
{

}

void TabSettings::on_jbossstartscript_edit_textChanged(const QString &arg1)
{

}

void TabSettings::on_jbossstartscript_edit_2_textChanged(const QString &arg1)
{

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
