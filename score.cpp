
#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    setPlainText(QString("Score: ") + QString::number(0));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void Score::showScore(int scr)
{
    setPlainText(QString("Score: ") + QString::number(scr)); // Health: 2
    this->show();
}

