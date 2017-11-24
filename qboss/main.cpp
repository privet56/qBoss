#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QSplashScreen>
#include <QApplication>
#include <QFile>
#include <QSystemTrayIcon>
#include <QTimer>
#include "util/tray.h"
#include "util/f.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(f::getResFn("res/bun.png"));
    QSplashScreen splash(pixmap, Qt::SplashScreen | Qt::WindowStaysOnTopHint);
    {   //splash
        //#ifndef _DEBUG
        splash.show();
        //#endif
        splash.showMessage("Loading...", Qt::AlignBottom, Qt::red);
        QTimer::singleShot(999, &splash, SLOT(close()));
    }
    {
        QFile styleFile(f::getResFn("/res/styles.css"));
        styleFile.open(QFile::ReadOnly);
        QString style(styleFile.readAll());
        //QMessageBox::warning( NULL, "Warnung",style, QMessageBox::Ok);
        a.setStyleSheet(style);
    }

    MainWindow w;

    tray trayIcon(QIcon(f::getResFn("/res/bunny_run.gif")), &w, &splash);
    {   //tray
        trayIcon.setup();
    }
    w.show();

    return a.exec();
}
