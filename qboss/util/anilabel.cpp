#include "anilabel.h"

anilabel::anilabel(QWidget *parent) : QLabel(parent)
{

}

bool anilabel::setani(QString sRes)
{
    QMovie* pMovie = new QMovie(sRes);
    connect(pMovie,SIGNAL(frameChanged(int)),this,SLOT(setLabelIcon(int)));
    if (pMovie->loopCount() != -1) //if movie doesn't loop forever, force it to
        connect(pMovie,SIGNAL(finished()),pMovie,SLOT(start()));
    pMovie->start();
    if(!pMovie->isValid())
    {
        //TODO: log correctly!
        //helpers::log("anibutton:setani NOT.ok("+sRes+"):"+QString::number(pMovie->isValid()), LOG_WRN, qApp, 0);
        qDebug()<<QImageReader::supportedImageFormats();
        return false;
    }
    return true;
}

void anilabel::setLabelIcon(int frame)   // member function that catches the frameChanged signal of the QMovie
{
    //if(!this->isChecked())return;
    Q_UNUSED(frame)
    QMovie* pMovie = (QMovie*)sender();
    this->setPixmap(pMovie->currentPixmap());
}
