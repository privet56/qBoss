#ifndef ANIOKLABEL_H
#define ANIOKLABEL_H

#include <QLabel>
#include <QMovie>
#include <QIcon>
#include <QDebug>
#include "util/anilabel.h"

class anioklabel : public anilabel
{
    Q_OBJECT

public:
    static const int i=3;
    const QString ANIRES_OK = "res/good.gif";
    const QString ANIRES_NOK = "res/wrong.gif";
    const QString ANIRES_INACTIVE = "res/inactive.gif";

    //see also on the bottom
    Q_ENUMS(OkState)
    enum OkState { OK, NOK, INACTIVE };

    void setAniState(OkState okstate);

public:
    explicit anioklabel(QWidget *parent = nullptr);

signals:

public slots:

};

//see also qRegisterMetaType<anioklabel::OkState>(); in the cpp
Q_DECLARE_METATYPE( anioklabel::OkState )

#endif // ANIOKLABEL_H
