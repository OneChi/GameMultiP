#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent=0);
    void showScore();
    void setScore(int num);
    int getScore();
    void increaseScore();
    void decreaseScore();

private:
    int v_score = 0;
};


#endif // SCORE_H
