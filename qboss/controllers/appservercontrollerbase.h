#ifndef APPSERVERCONTROLLERBASE_H
#define APPSERVERCONTROLLERBASE_H

#include <QObject>

class AppServerControllerBase : public QObject
{
    Q_OBJECT
public:
    explicit AppServerControllerBase(QObject *parent = nullptr);

signals:

public slots:
};

#endif // APPSERVERCONTROLLERBASE_H