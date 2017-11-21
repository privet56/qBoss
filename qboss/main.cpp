#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    {
        QFile styleFile(":/res/styles.css");
        styleFile.open(QFile::ReadOnly);
        QString style(styleFile.readAll());
        //QMessageBox::warning( NULL, "Warnung",style, QMessageBox::Ok);
        a.setStyleSheet(style);
    }
    MainWindow w;
    w.show();

    return a.exec();
}
