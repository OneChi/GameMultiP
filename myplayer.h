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
    QGraphicsRectItem * head;
    QGraphicsRectItem * pistol;
    void fire();
public slots:
        void setBody();
       //void slotMyPlayerMouse();
private:
      // char * v_name = "UNKNOWN";
       int health = 10;
       int score = 0;
};



#endif // MYPLAYER_H

