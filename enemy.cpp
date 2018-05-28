#include <enemy.h>
#include <stdlib.h> //rand()
#include <typeinfo>
#include "game.h"
#include "health.h"
#include <QDebug>
#include <qmath.h>
#include "bullet.h"
#include "score.h"


Enemy::Enemy()
{
    setRect(0,0,10,50);
    //таймер
    int random_number = rand() % 700+50;
    setPos(random_number,0);

}

Enemy::Enemy(qreal xpp,qreal ypp,qreal angle)
{
    setRect(0,0,10,50);
    setPos(xpp,ypp);
    setRotation(angle);
}

int Enemy::move()
{
    // перемещение парня
    int STEP_SIZE = 1;
    double theta = rotation()+90; // degrees

    double dy = STEP_SIZE * qSin(theta*(M_PI/180));
    double dx = STEP_SIZE * qCos(theta*(M_PI/180));
    // сделать поиск цели через сцену !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; ++i ){
        if(typeid(*(colliding_items[i])) == typeid(MyPlayer)){
         // scene()->removeItem(colliding_items[i]);
          //delete colliding_items[i];
          scene()->removeItem(this);
          delete this;
          return 1;
        } else if (typeid(*(colliding_items[i]))==typeid(Bullet)){
          hp--;
        }
    }

    if(this->hp < 0 ||
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
