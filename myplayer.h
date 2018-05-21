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

void keyPressEvent(QKeyEvent *event);


public slots:
       void spawn();
       //void slotMyPlayerMouse();
private:
       char * v_name = "UNKNOWN";
};



#endif // MYPLAYER_H

