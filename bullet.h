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
public slots:
        void move();
};







#endif // BULLET_H
