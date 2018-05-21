#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{
public:
    Health(QGraphicsItem * parent=0);
    void showHealth();
    int getHealth();
    void setHealth(int num);
    void increaseHealth();
    void decreaseHealth();
private:
    int v_health = 0;

};

#endif // HEALTH_H
