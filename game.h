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

#include <signal.h>
#include <cstdio>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <random>
#include <random>
#include <fcntl.h>
#include <set>
#include <algorithm>
#include <fstream>


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <sys/sem.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>


#include<thread>

class Bullet;

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    double pocket[4];
    /*
    pocket[0] - type of obj 0 - player 1 - enemy 2 - bullet 3 - big boss
    pocket[1] - x coord
    pocket[2] - y coord
    pocket[3] - rot coord
    size 4
    */

    void initial(/*int argc, char **argv*/);
    void clientWork();
    void consolListener(int sock);
    size_t sendAll(int sockfd, const void *buf, size_t len, int flags);
    size_t recvAll(int sockfd, void *buf, size_t len, int flags);


    /*GLOBAL VARIABLES*/
    int g_clientSock,g_serverSock;
    struct sockaddr_in g_clientAddr,g_serverAddr;
    int g_serverAddrLen,g_clientAddrLen;


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
    void enemy_listen();
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





    //void mouseMoveEvent(QMouseEvent *event);
    //void keyPressEvent(QKeyEvent *event);
   // void mousePressEvent(QMouseEvent *event);
   // void closeEvent(QCloseEvent * event);

};


#endif // GAME_H
