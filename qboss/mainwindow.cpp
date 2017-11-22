#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<int> sizes;
    sizes << 1; //top area
    sizes << 1; //bottom area (log wnd)
    this->ui->splitter->setSizes(sizes);
}

MainWindow::~MainWindow()
{
    delete ui;
}
