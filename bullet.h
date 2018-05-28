#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include <QtDebug>
#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <game.h>

#pragma once


class Bullet: public QObject,public QGraphicsRectItem {
    Q_OBJECT
public:
        Bullet();
        Bullet(qreal angle);
        int move();
        int hp = 1;
};







#endif // BULLET_H
