#include <myplayer.h>
#include <QtDebug>
#include <QEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "bullet.h"
#include "enemy.h"













//void MyPlayer::slotMyPlayerMouse(QPointF point)
//{
//    // Определяем расстояние до цели
//    target = point;
//    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
//    // Угол поворота в направлении к цели
//    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
//    if (lineToTarget.dy() < 0)
//        angleToTarget = TwoPi - angleToTarget;
//    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

//    /* В Зависимости от того, слева или справа находится Цель от Героя,
//     * устанавливаем направление поворота Героя в данном тике таймера
//     * */
//    if (angleToTarget >= 0 && angleToTarget < Pi) {
//        // Rotate left
//        setRotation(rotation() - angleToTarget * 180 /Pi);
//    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
//        // Rotate right
//        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
//    }
//}


//double angl
MyPlayer::MyPlayer()
{

    setRect(0,0,50,30);
    setTransformOriginPoint(25,15);


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




