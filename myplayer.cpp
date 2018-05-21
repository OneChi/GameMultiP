#include <myplayer.h>
#include <QtDebug>
#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "bullet.h"
#include "enemy.h"










void MyPlayer::keyPressEvent(QKeyEvent *event)
{

 //#if define DEBUG   qDebug() << "My Player do smth";
    if(event->key() == Qt::Key_Up) {
       setPos(x(),y()-10);
    }
    else if(event->key() == Qt::Key_Left) {
        if(pos().x() > 0){
       setPos(x()-10,y());
        }
    }
    else if(event->key() == Qt::Key_Right) {
       if(pos().x()+rect().width() < scene()->width()){
            setPos(x()+10,y());
        }
    }
    else if(event->key() == Qt::Key_Down) {
            setPos(x(),y()+10);
    }
    else if (event->key() == Qt::Key_Space ) {
        Bullet * bullet = new Bullet();
        bullet->setPos(x()+rect().width()/2,y());
        scene()->addItem(bullet);

//#if define DEBUG     qDebug() << "Bullet create";
    }
}




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


