#include "health.h"
#include <QFont>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){

    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void Health::showHealth()
{
    setPlainText(QString("Health: ") + QString::number(v_health)); // Health: 2
    this->show();
}


int Health::getHealth()
{
    return v_health;
}

void Health::setHealth(int num)
{
    v_health = num;
}


void Health::decreaseHealth()
{
v_health--;
setPlainText(QString("Health: ") + QString::number(v_health));
}

void Health::increaseHealth()
{
v_health++;
setPlainText(QString("Health: ") + QString::number(v_health));
}
