#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <list>

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
    Game(QWidget * parent = 0);     // конструктор
    MyPlayer * myIgrok1 = nullptr;  // игрок 1
    MyPlayer * myIgrok2 = nullptr;  // игрок 2
    //Score * score;
    //Health * health;
    QGraphicsScene * scene;         // сцена
    //Bullet * bul;
    void showGrid();                // показать сетку на экране
    void spawnEnemys();             // спан врагов по таймеру
    void gameSet();                 // сет и старт игры
    void gamePause();               // пауза

    void gameSetTest();

private:
    inline void slotMyPlayerMouse();
    void gamecycle();               // игровой цикл
    void spawn();
    bool pause = 1;                 // переменная паузы
    void setPlayer1();              // сет игрока 1
    void setPlayer2();              // сет игрока 2
    QTimer * gametimer;
    QTimer * enemy;            // taimer  zlodeyev
    QTimer * mouse;
    std::list<Enemy*>  EnemyList;
    std::list<Bullet*>  BulletList;
    std::list<MyPlayer*>  PlayerList;





    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent * event);

};


#endif // GAME_H
