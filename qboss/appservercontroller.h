#ifndef APPSERVERCONTROLLER_H
#define APPSERVERCONTROLLER_H

#include <QObject>

class AppServerController : public QObject
{
    Q_OBJECT
public:
    explicit AppServerController(QObject *parent = nullptr);

    bool setAppServerStartScript(QString sAppServerStartScript);

protected:
    QString m_sAppServerStartScript;
signals:

public slots:
};

#endif // APPSERVERCONTROLLER_H
