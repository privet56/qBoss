#ifndef TABBROWSER_H
#define TABBROWSER_H

#include <QWidget>

namespace Ui {
class tabBrowserUI;
}

class TabBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit TabBrowser(QWidget *parent = nullptr);
    ~TabBrowser();

private:
    Ui::tabBrowserUI *ui;

signals:

public slots:
private slots:
    void on_eUrl_returnPressed();
};

#endif // TABBROWSER_H
