#include "anioklabel.h"

anioklabel::anioklabel(QWidget *parent) : anilabel(parent)
{
    qRegisterMetaType<anioklabel::OkState>();
}

void anioklabel::setAniState(OkState okstate)
{
    switch (okstate) {
    case OkState::OK:
        this->setani(ANIRES_OK);
        this->setToolTip("OK");
        break;
    case OkState::NOK:
        this->setani(anioklabel::ANIRES_NOK);
        this->setToolTip("Not OK");
        break;
    case OkState::INACTIVE:
        this->setani(anioklabel::ANIRES_INACTIVE);
        this->setToolTip("Inactive");
        break;
    default:
        qDebug() << "anioklabel::setani ERR: no such OkState";
        break;
    }
}
