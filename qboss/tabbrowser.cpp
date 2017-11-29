#include "tabbrowser.h"
#include "ui_tabbrowser.h"

TabBrowser::TabBrowser(QWidget *parent) : QWidget(parent), ui(new Ui::tabBrowserUI), m_pLogger(nullptr)
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
void TabBrowser::closeEvent(QCloseEvent *evt)
{
    Q_UNUSED(evt);

    this->m_pLogger->GetCfg()->setValue(this->ui->eUrl->objectName(), this->ui->eUrl->text());
}
void TabBrowser::init(logger* pLogger)
{
    this->m_pLogger = pLogger;

    this->ui->eUrl->setText(this->m_pLogger->GetCfg()->getValue(this->ui->eUrl->objectName()));
}
