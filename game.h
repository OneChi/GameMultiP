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
    MyPlayer * myIgrok = nullptr;
    //Score * score;
    //Health * health;
    QGraphicsScene * scene;
    Bullet * bul;
    void showGrid();
    void spawnEnemys();
    void gameSet();
    void gamePause();
public slots:
    void spawn();
//private slots:
    //
private:
    bool pause = 1;
    void setPlayer();
    QTimer * enemy; // taimer  zlodeyev
    QPointF target;
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent * event);
    void keyPressW(QKeyEvent *event);
};


#endif // GAME_H
