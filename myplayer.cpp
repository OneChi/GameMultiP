#include <myplayer.h>
#include <QtDebug>
#include <QEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "bullet.h"
#include "enemy.h"


//double angl
MyPlayer::MyPlayer()
{

    setRect(0,0,50,30);
    setTransformOriginPoint(25,15);
    setTransform(transform().rotate(90));

    QTimer * timer = new QTimer();
    timer->start(15);
}


MyPlayer::~MyPlayer()
{
    delete this;
}

void MyPlayer::fire()
{

    Bullet * bullet = new Bullet();
    bullet->setPos( x()+ rect().width()/2, y());
    bullet->setRotation(rotation());

    scene()->addItem(bullet);
}




