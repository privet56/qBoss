#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>
#include <QMessageBox>
#include "util/str.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_cfg(this),
    m_logger(nullptr, nullptr, this)
{
    ui->setupUi(this);

    this->m_logger.init(&this->m_cfg, this->ui->logWindow);
    this->ui->settingsWidget->init(&this->m_logger);

    QList<int> sizes;
    sizes << 1; //top area
    sizes << 1; //bottom area (log wnd)
    this->ui->splitter->setSizes(sizes);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::closeEvent( QCloseEvent *evt )
{
    Q_UNUSED( evt );
    //QMessageBox::warning( NULL, "mainwindow","close", QMessageBox::Ok);
  //foreach (QWidget *widget, QApplication::topLevelWidgets()) {
    //widget->close();
   //}
}*/
