#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "util/cfg.h"
#include "util/logger.h"
#include "util/logwnd.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    logger m_logger;
    cfg m_cfg;

protected:
    void closeEvent(QCloseEvent *evt);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
