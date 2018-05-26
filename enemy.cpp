#include <enemy.h>
#include <stdlib.h> //rand()
#include <typeinfo>
#include "game.h"
#include "health.h"

#include "score.h"


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

Enemy::Enemy(qreal xpp,qreal ypp)
{
    setRect(0,0,10,50);
    //таймер
    //int random_number = rand() % 300;
    setPos(xpp,ypp);
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

/*
void Tower::aquire_target(){
    // get a list of all items colliding with attack_area
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    if (colliding_items.size() == 1){
        has_target = false;
        return;
    }

    double closest_dist = 300;
    QPointF closest_pt = QPointF(0,0);
    for (size_t i = 0, n = colliding_items.size(); i < n; i++){
        Enemy * enemy = dynamic_cast<Enemy *>(colliding_items[i]);
        if (enemy){
            double this_dist = distanceTo(enemy);
            if (this_dist < closest_dist){
                closest_dist = this_dist;
                closest_pt = colliding_items[i]->pos();
                has_target = true;
            }
        }
    }

    attack_dest = closest_pt;
    fire();


double Tower::distanceTo(QGraphicsItem *item){
    QLineF ln(pos(),item->pos());
    return ln.length();
}

void Enemy::rotateToPoint(QPointF p){
    QLineF ln(pos(),p);
    setRotation(-1 * ln.angle());
}


}*/
