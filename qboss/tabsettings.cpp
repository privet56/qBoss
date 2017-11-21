#include "tabsettings.h"
#include "ui_tabsettings.h"

TabSettings::TabSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabSettings)
{
    ui->setupUi(this);
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
