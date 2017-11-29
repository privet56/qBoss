#include "tabbrowser.h"
#include "ui_tabbrowser.h"

TabBrowser::TabBrowser(QWidget *parent) : QWidget(parent), ui(new Ui::tabBrowserUI), m_pLogger(nullptr)
{
    ui->setupUi(this);
    //this->ui->browser->load(QUrl("http://www.google.de/"));
    QWebEngineView* pBrowser = this->ui->browser;

    connect(pBrowser,SIGNAL(loadFinished(bool)), this, SLOT(browserLoadFinished(bool)));
    connect(pBrowser,SIGNAL(loadStarted()), this, SLOT(browserLoadStarted()));
    connect(pBrowser,SIGNAL(urlChanged(const QUrl)), this, SLOT(browserUrlChanged(const QUrl)));
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
    this->m_pLogger->GetCfg()->setValue(this->ui->eUrl->objectName(), this->ui->eUrl->text());
}
void TabBrowser::browserLoadFinished(bool ok)
{
    Q_UNUSED(ok)

    this->ui->eUrl->setProperty("loading", false);
    this->ui->eUrl->style()->unpolish(this->ui->eUrl);
    this->ui->eUrl->style()->polish(this->ui->eUrl);
}
void TabBrowser::browserLoadStarted()
{
    this->ui->eUrl->setProperty("loading", true);
    this->ui->eUrl->style()->unpolish(this->ui->eUrl);
    this->ui->eUrl->style()->polish(this->ui->eUrl);
}
void TabBrowser::browserUrlChanged(const QUrl url)
{
    this->ui->eUrl->setText(url.toString());
}
void TabBrowser::closeEvent(QCloseEvent *evt)
{
    Q_UNUSED(evt);
    //this->m_pLogger->GetCfg()->setValue(this->ui->eUrl->objectName(), this->ui->eUrl->text());    //better save on [ENTER]
}
void TabBrowser::init(logger* pLogger)
{
    this->m_pLogger = pLogger;
    this->ui->eUrl->setText(this->m_pLogger->GetCfg()->getValue(this->ui->eUrl->objectName()));
}
