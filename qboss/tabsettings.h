#ifndef TABSETTINGS_H
#define TABSETTINGS_H

#include <QWidget>
#include "util/cfg.h"
#include "util/logger.h"

namespace Ui {
class TabSettings;
}

class TabSettings : public QWidget
{
    Q_OBJECT

public:
    explicit TabSettings(QWidget *parent = 0);
    ~TabSettings();

public:
    void init(logger* pLogger);
    logger* m_pLogger;
    void activateAnis(QObjectList& children);

protected:
    bool eventFilter(QObject * obj, QEvent * event);
    void onCfg(QObjectList& children, int recDepth, bool bRead);

private slots:

    void on_startB_clicked();
    void on_stopB_clicked();
    void on_restartB_clicked();

    void on_jbossstartscript_edit_textChanged(const QString &arg1);
    void on_jbossstartscript_browse_clicked();

private:
    Ui::TabSettings *ui;
};

#endif // TABSETTINGS_H
