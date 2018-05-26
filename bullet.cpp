#include "bullet.h"
#include "enemy.h"
#include <typeinfo>
#include "health.h"
#include <QPixmap>
#define _USE_MATH_DEFINES
#include <QGraphicsPixmapItem>
#include <qmath.h>
#include "score.h"
#include "myevent.h"

//extern MainMenu * game;
Bullet::Bullet()
{
    setRect(0,0,10,50);
    //таймер
    rotate(90);
    QTimer * timer = new QTimer();
    //cвязывание функции move с таймером
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    //таймаут таймера
    timer->start(40);
}
double degreesToRadians(double degrees) {
    return degrees * (M_PI / 180);
}

/*
void Bullet::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; ++i ){
        if(typeid(*(colliding_items[i])) == typeid(Enemy)){
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            scene()->removeItem(this);

            delete this;
            return;
        }
    }




    setPos(x(),y()-10); // перемещение пули

}*/

    void Bullet::move(){

        int STEP_SIZE = 10;
        double theta = rotation(); // degrees

        double dy = STEP_SIZE * qSin(degreesToRadians(theta));
        double dx = STEP_SIZE * qCos(degreesToRadians(theta)); 
        QList<QGraphicsItem *>  colliding_items = collidingItems();
        for(int i = 0, n = colliding_items.size(); i < n; ++i ){
            if(typeid(*(colliding_items[i])) == typeid(Enemy)){
                scene()->removeItem(colliding_items[i]);
                delete colliding_items[i];
                  //  QApplication::sendEvent(colliding_items[i],myevent::myType);
                scene()->removeItem(this);

                delete this;
                return;
            }
        }
        setPos(x()+dx, y()+dy);

        // условие удаления пули - выход за пределы экрана
        if(
                pos().y()+rect().height() < 0                  ||
                pos().x()+rect().height() < 0                  ||
                pos().x()-rect().height() > scene()->width() ||
                pos().y()-rect().height() > scene()->height()
           ){
            scene()->removeItem(this);
            delete this;
            //qDebug() << "DEL";
        }

    }
