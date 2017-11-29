#ifndef TABBROWSER_H
#define TABBROWSER_H

#include <QWidget>
#include "util/cfg.h"
#include "util/logger.h"

namespace Ui {
class tabBrowserUI;
}

class TabBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit TabBrowser(QWidget *parent = nullptr);
    ~TabBrowser();
public:
    void closeEvent(QCloseEvent *evt);
    void init(logger* pLogger);
protected:
    logger* m_pLogger;

private:
    Ui::tabBrowserUI *ui;

signals:

public slots:
private slots:
    void on_eUrl_returnPressed();

    void browserLoadFinished(bool ok);
    void browserLoadStarted();
    void browserUrlChanged(const QUrl url);

};

#endif // TABBROWSER_H
