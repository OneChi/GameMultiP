#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    setPlainText(QString("Score: ") + QString::number(v_score));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void Score::showScore()
{
    setPlainText(QString("Score: ") + QString::number(v_score)); // Health: 2
    this->show();
}

void Score::setScore(int num)
{
    this->v_score = num;
}

int Score::getScore()
{
    return  this->v_score;
}
void Score::increaseScore()
{
 this->v_score++;
    setPlainText(QString("Score: ") + QString::number(v_score));
}
void Score::decreaseScore()

{

 this->v_score--;
    setPlainText(QString("Score: ") + QString::number(v_score));
}
