#ifndef TRAY_H
#define TRAY_H

#include <QObject>
#include <QAction>
#include <QMovie>
#include <QSystemTrayIcon>
#include <QSplashScreen>

class QBalloonTip;

class tray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit tray(QObject *parent, QSplashScreen* pSplash);
    explicit tray(const QIcon &icon, QObject *parent, QSplashScreen* pSplash);
    void setup();

    static tray* getTrayIcon();

protected:
    QMovie m_movie;
    QAction* m_paHideorShow;
    QSplashScreen* m_pSplash;

signals:

public slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);
    void on_actionShow_Mascot();
    void onIconUpdate();
    void onAbout();
    void hide_show();
    void showIfHidden();
};

#endif // TRAY_H
