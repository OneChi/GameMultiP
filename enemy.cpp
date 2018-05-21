#include <enemy.h>
#include <stdlib.h> //rand()
#include <typeinfo>
#include "game.h"
#include "health.h"

#include "score.h"

extern Game * myGame;

Enemy::Enemy()
{
    setRect(0,0,10,50);
    //таймер
    int random_number = rand() % 300;
    setPos(random_number,0);
    QTimer * timer = new QTimer();
    //cвязывание функции move с таймером
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    //таймаут таймера
    timer->start(24);
}

void Enemy::move()
{

    setPos(x(),y()+1); // перемещение парня
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; ++i ){
        if(typeid(*(colliding_items[i])) == typeid(MyPlayer)){
            myGame->health->decreaseHealth();
         // scene()->removeItem(colliding_items[i]);
          //delete colliding_items[i];
          scene()->removeItem(this);

          delete this;
          return;
        }
    }
    // условие удаления парня - выход за пределы экрана
    if(pos().y()-rect().height() > scene()->height()){
        scene()->removeItem(this);
        delete this;
       // qDebug() << "deleted";
    }
}

