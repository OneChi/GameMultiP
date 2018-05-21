#include "bullet.h"
#include "enemy.h"
#include <typeinfo>
#include "health.h"
#include "score.h"

//extern MainMenu * game;
extern Game * myGame;
Bullet::Bullet()
{
    setRect(0,0,10,50);
    //таймер

    QTimer * timer = new QTimer();
    //cвязывание функции move с таймером
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    //таймаут таймера
    timer->start(40);
}



void Bullet::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; ++i ){
        if(typeid(*(colliding_items[i])) == typeid(Enemy)){
              myGame->score->increaseScore();

            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            scene()->removeItem(this);

            delete this;
            return;
        }
    }


    setPos(x(),y()-10); // перемещение пули
    // условие удаления пули - выход за пределы экрана
    if(pos().y()+rect().height()< 0){
        scene()->removeItem(this);
        delete this;
    }
}
