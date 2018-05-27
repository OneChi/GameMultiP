#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include <QtDebug>
#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>


class Enemy: public QObject,public QGraphicsRectItem {
    Q_OBJECT
public:
        Enemy();
        Enemy(qreal xpp,qreal ypp);
        int hp = 10;
public slots:
        void move();
private:


};

#endif // ENEMY_H
