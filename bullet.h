#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include <QtDebug>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QList>
#include <game.h>

#pragma once


class Bullet: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
        Bullet(QGraphicsPixmapItem *parent = 0);
        Bullet(qreal angle);
        int move();
        int hp = 1;
};







#endif // BULLET_H
