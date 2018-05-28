#include "bullet.h"
#include "enemy.h"
#include <typeinfo>
#include <QDebug>
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
    setTransform(transform().rotate(90));

}

Bullet::Bullet(qreal angle)
{
    setRect(0,0,10,50);
    setRotation(angle);
    setTransform(transform().rotate(90));
}


double degreesToRadians(double degrees) {
    return degrees * (M_PI / 180);
}



    int Bullet::move()
    {
        // перемещение парня
        int STEP_SIZE = 10;
        double theta = rotation(); // degrees

        double dy = STEP_SIZE * qSin(theta*(M_PI/180));
        double dx = STEP_SIZE * qCos(theta*(M_PI/180));
        // сделать поиск цели через сцену !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        QList<QGraphicsItem *> colliding_items = collidingItems();
        for(int i = 0, n = colliding_items.size(); i < n; ++i ){
            if(typeid(*(colliding_items[i])) == typeid(Enemy)){
             // scene()->removeItem(colliding_items[i]);
              //delete colliding_items[i];
              scene()->removeItem(this);
              delete this;
              hp--;
              return 1;
            }
        }

        if(this->hp <= 0 ||
                pos().y()+rect().height() < 0                  ||
                pos().x()+rect().height() < 0                  ||
                pos().x()-rect().height() > scene()->width() ||
                pos().y()-rect().height() > scene()->height()
           ){
            scene()->removeItem(this);
            delete this;
            return 1;

            //qDebug() << "DEL";
        }




        setPos(x()+dx, y()+dy);
        return 0;
    }
