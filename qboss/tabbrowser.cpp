#include "tabbrowser.h"
#include "ui_tabbrowser.h"

TabBrowser::TabBrowser(QWidget *parent) : QWidget(parent), ui(new Ui::tabBrowserUI)
{
    ui->setupUi(this);
    //this->ui->browser->load(QUrl("http://www.google.de/"));
}

TabBrowser::~TabBrowser()
{
    delete ui;
}

void TabBrowser::on_eUrl_returnPressed()
{
    QString sTxt(this->ui->eUrl->text());
    if(!sTxt.toLower().startsWith("http"))
    {
        sTxt = "http://"+sTxt;
        this->ui->eUrl->setText(sTxt);
    }
    this->ui->browser->load(QUrl(sTxt));
}
