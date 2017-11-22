#ifndef TABSETTINGS_H
#define TABSETTINGS_H

#include <QWidget>

namespace Ui {
class TabSettings;
}

class TabSettings : public QWidget
{
    Q_OBJECT

public:
    explicit TabSettings(QWidget *parent = 0);
    ~TabSettings();

    void activateAnis(QObjectList& children);

private slots:
    void on_jbossstartscript_browse_pressed();

    void on_jbossstartscript_browse_2_pressed();

    void on_jbossstartscript_edit_textChanged(const QString &arg1);

    void on_jbossstartscript_edit_2_textChanged(const QString &arg1);

    void on_startB_clicked();

    void on_stopB_clicked();

    void on_restartB_clicked();

private:
    Ui::TabSettings *ui;
};

#endif // TABSETTINGS_H
