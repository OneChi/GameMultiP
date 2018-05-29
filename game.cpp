#include <stdlib.h>
#include <QTimer>
#include <QLineF>
#define _USE_MATH_DEFINES
#include <QGraphicsPixmapItem>
#include <QObject>
#include <qmath.h>
#include <QFont>
#include <QGraphicsScene>
#include <QtMultimedia>

#include "bullet.h"
#include "score.h"
#include "health.h"
#include "myevent.h"
#include "game.h"
#include "myplayer.h"
#include "enemy.h"

QPointF * target;
qreal angleToTarget  = 0;







//  CONSTRUCTOR
void Game::initial(/*int argc, char **argv*/)
{
    char * argv2 = "52525";
    char * argv1 = "192.168.1.63";
    //CLIENT
    bzero(&g_clientAddr,sizeof(g_clientAddr));
    g_clientAddr.sin_family = AF_INET;
    g_clientAddr.sin_port = htons(0);
    g_clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //SERVER
    bzero(&g_serverAddr,sizeof(g_serverAddr));
    g_serverAddr.sin_family = AF_INET;
    g_serverAddr.sin_port = htons(atoi(argv2));
    if(inet_aton(argv1,&g_serverAddr.sin_addr)==0)
        {
         qDebug() << "INVALID IP";
         //close(udp_clientSock);
         exit(1);
        }

    //CLIENT SOCKET
    if((g_clientSock = socket(AF_INET, SOCK_STREAM, 0))<0)
        {
           qDebug()<<"socket ";
            exit(1);
        }

    int opt = 1;
    //CLIENT SOCKOPT
    if(setsockopt(g_clientSock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))==-1)
    {
        qDebug()<<"sockopt ";
    }

    //CLIENT BIND
    if(bind(g_clientSock, (struct sockaddr *)&g_clientAddr, sizeof(g_clientAddr)) < 0)
    {
       qDebug() <<"bind cli";
        exit(2);
    }

}

void Game::clientWork()
{
    if(::connect(g_clientSock, (struct sockaddr *)&g_serverAddr, sizeof(g_serverAddr)) < 0)
    {
       perror("connect");
       exit(2);
    }
    char name[11] = {"ALEXEY1234"};
    sendAll(g_clientSock,name,sizeof(name),NULL);
}

void Game::consolListener(int sock)
{
    return ;
}

size_t Game::sendAll(int sockfd, const void *buf, size_t len, int flags)
{
    size_t sended = 0;
        while (sended < len) {
            int i = send(sockfd, static_cast<const void*>(static_cast<const char*>(buf) + sended), len - sended, flags);
            if (i <= 0) {
                return i;
            }
            sended += i;
        }
        return sended;
}

size_t Game::recvAll(int sockfd, void *buf, size_t len, int flags)
{
    size_t receved = 0;
        while (receved < len) {
            int i = recv(sockfd, static_cast<void*>(static_cast<char*>(buf) + receved), len - receved, flags);
            if (i <= 0) {
                return i;
            }
            receved += 	i;
        }
        return receved;
}

Game::Game(QWidget * parent)
{
    initial();
    clientWork();
    Q_UNUSED(parent)
   scene = new QGraphicsScene();
   scene->setSceneRect(0,0,800,800);
   setScene(scene);
   setFixedSize(810,810);
   setMouseTracking(true);

   mouse = new QTimer();
   gametimer = new QTimer();
   enemy = new QTimer();

   target = new QPointF();

 //QObject::connect(&timer, &QTimer::timeout,&listenerObject,
 //                 &OnTimerTickListener::onTimerTick);
 //QObject::connect(gametimer,SIGNAL(timeout()),this,SLOT(gamecycle()));
   QObject::connect(enemy, &QTimer::timeout,this,&Game::spawn);
   QObject::connect(mouse, &QTimer::timeout,this,&Game::slotMyPlayerMouse);
   QObject::connect(gametimer, &QTimer::timeout,this,&Game::gamecycle);

    mouse->start(2);
    gametimer->start(10);

    gameSet();

    // Play Background music

}

// вращение за мышкой
inline void Game::slotMyPlayerMouse()
{
    myIgrok1->setRotation(angleToTarget);
}

//  нормализация угла в градусах
static qreal normalizeAngle(qreal angle){
       //qDebug() <<"ANGLE:   " << angle;
    while (angle < 0)
        angle += M_2_PI;
    while (angle > M_2_PI)
        angle -= M_2_PI;

    return angle;
}

//  спавн врагов - функция для таймера
void Game::spawn()
{
    Enemy * enemy = new Enemy();
    scene->addItem(enemy);
    EnemyList.push_back(enemy);
}

//  инициализация игрока 1
void Game::setPlayer1()
{
    myIgrok1 = new MyPlayer();
}

//  инициализация игрока 2
void Game::setPlayer2()
{
    myIgrok2 = new MyPlayer();

    //myIgrok2->setRect(0,0,50,30);


}

//  показать сетку на экране
void Game::showGrid()
{
    QGraphicsLineItem * lineGrid[82];
    for (auto i = 0; i < 82; i++){
        lineGrid[i] = new QGraphicsLineItem();
        //lineGrid[i]->setPen();
    }
    for (auto i = 0,x1 =0,x2 = 0,y1 =0,y2 = 800; i < 41; i++){

        lineGrid[i]->setLine(x1,y1,x2,y2);
        lineGrid[i+41]->setLine(y1,x1,y2,x2);
        x1+=20;
        x2+=20;
        scene->addItem(lineGrid[i+41]);
        scene->addItem(lineGrid[i]);
        //lineGrid[i]->show();
    }
}

//  таймер спавна врагов
void Game::spawnEnemys()
{
    enemy->start(2000);
}

//  сет и старт игры
void Game::gameSet()
{

    pause = 0;
    setPlayer1();
    setPlayer2();
    scene->addItem(myIgrok2);
    myIgrok2->setPos(600,400);
    //myIgrok2->transform().rotate(45);
    myIgrok2->setTransform(transform().rotate(90));
    myIgrok1->setPos(200,400);
    //add item on the scene
    scene->addItem(myIgrok1);
    //MAKE PLAYER FOCUS



    myIgrok1->setFlag(QGraphicsItem::ItemIsFocusable);
    myIgrok1->setFocus();

     spawnEnemys();
}

//  игровая пауза / не работает пауза таймеров!!!
void Game::gamePause()
{
       pause = 1;
       //enemy->stop();

}

void Game::gameSetTest()
{
    pause = 0;
    setPlayer1();
    myIgrok1->setPos(200,400);
    //add item on the scene
    scene->addItem(myIgrok1);
    //MAKE PLAYER FOCUS



    myIgrok1->setFlag(QGraphicsItem::ItemIsFocusable);
    myIgrok1->setFocus();

}

void Game::gamecycle()
{
     for ( std::list<Enemy *>::const_iterator i = EnemyList.begin();i != EnemyList.end(); ++i ) {
        if((*i)->move()){
          EnemyList.remove((*i));
          break;
        }
     }

     for ( std::list<Bullet *>::const_iterator i = BulletList.begin();
           i != BulletList.end(); ++i ) {
         if((*i)->move()){
           BulletList.remove((*i));
           break;
         }
     }

     qDebug() << BulletList.size();
}

//  обработка нажатий клавиатуры
void Game::keyPressEvent(QKeyEvent *event)
{
    if(!pause){
 //#if define DEBUG   qDebug() << "My Player do smth";
    if(event->key() == Qt::Key_Up) {
       myIgrok1->setPos( myIgrok1->x(), myIgrok1->y()-10);
    }
    else if(event->key() == Qt::Key_Left) {
        if( myIgrok1->pos().x() > 0){
        myIgrok1->setPos( myIgrok1->x()-10, myIgrok1->y());
        }
    }
    else if(event->key() == Qt::Key_Right) {
       if( myIgrok1->pos().x()+ myIgrok1->rect().width() < scene->width()){
             myIgrok1->setPos( myIgrok1->x()+10, myIgrok1->y());
        }
    }
    else if(event->key() == Qt::Key_Down) {
             myIgrok1->setPos( myIgrok1->x(), myIgrok1->y()+10);
    }
    else if (event->key() == Qt::Key_Space ) {
        //myIgrok1->fire();

        Bullet * bullet1 = new Bullet();
        bullet1->setPos( myIgrok1->x()+ myIgrok1->rect().width()/2, myIgrok1->y());
        bullet1->setRotation(myIgrok1->rotation());
        scene->addItem(bullet1);
        BulletList.push_back(bullet1);

    }else if(event->key() == Qt::Key_P)
        {
            gamePause();
        }
    }


}

//  обработка нажатия кнопок мышки
void Game::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event)
    //create a bullet
    Bullet * bullet1 = new Bullet();
    bullet1->setPos( myIgrok1->x()+ myIgrok1->rect().width()/2, myIgrok1->y());
    bullet1->setRotation(myIgrok1->rotation());
    scene->addItem(bullet1);
    BulletList.push_back(bullet1);
}

// ИСРАВИТЬ!!!!
void Game::mouseMoveEvent(QMouseEvent *event) {
   //myIgrok->setPos( event->pos().x()-20,event->pos().y()-20);

    target->setX(event->pos().x());
    target->setY(event->pos().y());


    QLineF lineToTarget(QPointF(myIgrok1->pos().x(), myIgrok1->pos().y()), target->toPoint());
//qreal
    angleToTarget = acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() > 0){
        angleToTarget = (angleToTarget * 180) /M_PI;
    }else{
        angleToTarget = (angleToTarget * 180) /M_PI*-1;
    }
      //qDebug() << angleToTarget;
}

//  ззакрытие крестиком
void Game::closeEvent(QCloseEvent *event)
{
    event->ignore();
   // MainMenu * newMenu = new MainMenu();
    //newMenu->show();
    this->close();
    delete this;
    event->accept();
}



