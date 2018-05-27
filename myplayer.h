#ifndef MYPLAYER_H
#define MYPLAYER_H
#include <QTimer>
#include <QObject>
#include <QtDebug>
#include <QEvent>
#include <string>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <enemy.h>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>


class MyPlayer: public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    MyPlayer();
    ~MyPlayer();
    void fire();
public slots:

private:
      // char * v_name = "UNKNOWN";
       int health = 10;
       int score = 0;
};



#endif // MYPLAYER_H

