#include "health.h"
#include <QFont>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){

    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void Health::showHealth(int hp)
{
    setPlainText(QString("Health: ") + QString::number(hp)); // Health: 2
    this->show();
}

