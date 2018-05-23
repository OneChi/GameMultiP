#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>

#include "score.h"
#include "health.h"
#include "bullet.h"
#include "enemy.h"
#include "myplayer.h"

class Bullet;

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent = 0);
    MyPlayer * myIgrok;
    //Score * score;
    //Health * health;
    QGraphicsScene * scene;
    Bullet * bul;
    void showGrid();
    void spawnEnemys();
public slots:
    void spawn();
private:
    QTimer * enemy;
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent * event);
};


#endif // GAME_H
