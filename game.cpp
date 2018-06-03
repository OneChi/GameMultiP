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
#include <QDebug>
#include <cstdlib>
#include <QValidator>
#include <QKeyEvent>

#include "bullet.h"
#include "score.h"
#include "health.h"
#include "myevent.h"
#include "game.h"
#include "myplayer.h"
#include "enemy.h"

/*
pocket[0] - type of obj 0 - player 1 - enemy 2 - bullet 3 - big boss
pocket[1] - x coord
pocket[2] - y coord
pocket[3] - rot coord
size 4
*/

QPointF * target;
qreal angleToTarget  = 0;


Game::Game(QWidget * parent)
{

    Q_UNUSED(parent)


    initial();
   clientWork();

   scene = new QGraphicsScene();
   scene->setSceneRect(0,0,800,800);
   setScene(scene);
   setFixedSize(810,810);
   setMouseTracking(true);

   mouse = new QTimer();
   gametimer = new QTimer();
   enemy = new QTimer();
   onlineDEALS = new QTimer();
   target = new QPointF();

 //QObject::connect(&timer, &QTimer::timeout,&listenerObject,
 //                 &OnTimerTickListener::onTimerTick);
 //QObject::connect(gametimer,SIGNAL(timeout()),this,SLOT(gamecycle()));
   QObject::connect(enemy, &QTimer::timeout,this,&Game::spawn);
   QObject::connect(mouse, &QTimer::timeout,this,&Game::slotMyPlayerMouse);
   QObject::connect(gametimer, &QTimer::timeout,this,&Game::gamecycle);


   QObject::connect(onlineDEALS, &QTimer::timeout,this,&Game::enemy_listen);
   QObject::connect(onlineDEALS, &QTimer::timeout,this,&Game::send_data_to_ser);




   // int state = 0;
    //while(state ==  0)
    //recvAll(g_clientSock,&state,sizeof(int),NULL);
   // qDebug()<< state;
   //gameSet();
    gameSet();


            backgroundMusic  = new QMediaPlayer();
            //QMediaPlayer * = new QMediaPlayer();
            //QMediaPlayer * = new QMediaPlayer();





            backgroundMusic->setMedia(QUrl("qrc:/new/SOUNDS/SOUNDS/bground.mp3"));

            sounds = new QMediaPlayer[20];
            sounds[0].setMedia(QUrl("qrc:/SOUNDS/SOUNDS/gun_revolver_pistol_shot_04.wav"));
            sounds[1].setMedia(QUrl("qrc:/SOUNDS/SOUNDS/bullet_impact_concrete_brick_01.wav"));
            sounds[2].setMedia(QUrl("qrc:/SOUNDS/SOUNDS/bullet_impact_body_thump_02.wav"));
            sounds[3].setMedia(QUrl("qrc:/SOUNDS/SOUNDS/voice_fun_character_cute_cartoon_23.wav"));
            sounds[4].setMedia(QUrl("qrc:/SOUNDS/SOUNDS/voice_fun_man_character_deep_laugh_11.wav"));
            sounds[5].setMedia(QUrl("qrc:/SOUNDS/SOUNDS/voice_fun_small_character_emote_interested_09.wav"));
            sounds[6].setMedia(QUrl("qrc:/SOUNDS/SOUNDS/voice_fun_small_character_emote_sad_02.wav"));
            sounds[7].setMedia(QUrl("qrc:/SOUNDS/SOUNDS/voice_male_b_battle_shout_short_09.wav"));
            sounds[8].setMedia(QUrl("qrc:/SOUNDS/SOUNDS/voice_male_b_death_low_09.wav"));
            sounds[9].setMedia(QUrl("qrc:/SOUNDS/SOUNDS/015_Foley_Footsteps_Asphalt_Boot_Walk_Fast_Run_Jog_Close.wav"));

            // Play Background music
            //backgroundMusic->play();




    gametimer->start(10);
    onlineDEALS->start(10);
    mouse->start(2);



}
void Game::playMedia(unsigned int media)
{



}
//  сет и старт игры
void Game::gameSet()
{

    pause = 0;
    setPlayer1();
    setPlayer2();
    scene->addItem(myIgrok2);
    //myIgrok2->setPos(600,400);
    //myIgrok2->transform().rotate(45);
    //myIgrok2->setTransform(transform().rotate(90));
   // myIgrok1->setPos(200,400);
    //add item on the scene
    scene->addItem(myIgrok1);
    //MAKE PLAYER FOCUS



    //myIgrok1->setFlag(QGraphicsItem::ItemIsFocusable);
   // myIgrok1->setFocus();

    //spawnEnemys();
}

void Game::enemy_listen()
{
    int EnemyCount = 0;
    int BulletCount = 0;

    recvAll(g_clientSock,&EnemyCount,sizeof(int),NULL);
   // qDebug() <<"ENEMY COUNT: "<< EnemyCount;
    for (int i = 0; i < EnemyCount; ++i){
        recvAll(g_clientSock,&pocket,sizeof(pocket),NULL);
        Enemy * buf = new Enemy();
        buf->setPos(pocket[1],pocket[2]);
        buf->setRotation(pocket[3]);
        EnemyList.push_back(buf);
       // qDebug() <<"ENEMY: "<< buf->pos().x()<<"   "<< buf->pos().y();
    }

    recvAll(g_clientSock,&BulletCount,sizeof(BulletCount),NULL);
   // qDebug() <<"BULLET COUNT: "<< BulletCount;
    for (int i = 0; i < BulletCount; ++i){
        recvAll(g_clientSock,&pocket,sizeof(pocket),NULL);
        Bullet * buf = new Bullet();
        buf->setPos(pocket[1],pocket[2]);
        buf->setRotation(pocket[3]);
        BulletList.push_back(buf);
       // qDebug() <<"ENEMY: "<< buf->pos().x()<<"   "<< buf->pos().y();
    }



    for(int i = 0; i < 2; ++i){
        recvAll(g_clientSock,&pocket,sizeof(pocket),NULL);
        if(pocket[0] == 0){
            //myIgrok2->setPos(pocket[1]+200,pocket[2]-20);
            myIgrok1->setPos(pocket[1],pocket[2]);

        }else if(pocket[0] == 4){
            //myIgrok1->setPos(pocket[1],pocket[2]);
            myIgrok2->setPos(pocket[1],pocket[2]);
            myIgrok2->setRotation(pocket[3]);
        }
    }




      //
    for ( std::list<Enemy *>::const_iterator i = EnemyList.begin();
          i != EnemyList.end(); ++i ) {
        scene->addItem((*i));
    }
    for ( std::list<Bullet *>::const_iterator i = BulletList.begin();
          i != BulletList.end(); ++i ) {
        scene->addItem((*i));
    }
    recvAll(g_clientSock,&music,sizeof(music),NULL);
    for (int i = 0; i < 20; ++i){
        if(music[i] == 1){
            if(i < 10){
                if(sounds[i].state() == QMediaPlayer::PlayingState){
                    sounds[i].setPosition(0);
                }else if(sounds[i].state() == QMediaPlayer::StoppedState){
                    sounds[i].play();
                }

            }else{
                if(sounds[i-10].state() == QMediaPlayer::PlayingState){
                    sounds[i-10].setPosition(0);
                }else if(sounds[i-10].state() == QMediaPlayer::StoppedState){
                    sounds[i-10].play();
                }

            }
        }
    }
}
// ДОРАБОТАТЬ ОТПРАВКУ ИГРОКА И ПУЛЬ
void Game::send_data_to_ser()
{



    sendAll(g_clientSock, &actions, sizeof(actions),NULL);


    //double actions[7];
    /*
     * actions[0] - key_up
     * actions[1] - key_left
     * actions[2] - key_right
     * actions[3] - key_down
     * actions[4] - key_space
     * actions[5] - rotation
     * actions[7] - pause
     * size 7
     */

}
void Game::gamecycle()
{
    if (EnemyList.size() != 0)
    for ( std::list<Enemy *>::const_iterator i = EnemyList.begin();i != EnemyList.end(); ++i ) {
        scene->removeItem((*i));
        delete (*i);
    }
    EnemyList.clear();
    if (BulletList.size() != 0)
    for ( std::list<Bullet*>::const_iterator i = BulletList.begin();i != BulletList.end(); ++i ) {
        scene->removeItem((*i));
        delete (*i);
    }
    BulletList.clear();


    //enemy_listen();
    //send_data_to_ser();
/*Enemy Single
     for ( std::list<Enemy *>::const_iterator i = EnemyList.begin();i != EnemyList.end(); ++i ) {
        if((*i)->move()){
          EnemyList.remove((*i));
          break;
        }
     }
*/
/*Bullet Single
    for ( std::list<Bullet *>::const_iterator i = BulletList.begin();
           i != BulletList.end(); ++i ) {
         if((*i)->move()){
           BulletList.remove((*i));
           break;
         }
     }
*/




}

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
void Game::keyPressEvent(QKeyEvent * event) {
    if (event->key() == Qt::Key_Up){
        actions[0] = 1;
    }  else if (event->key() ==  Qt::Key_Down){
        actions[1] = 1;
    }  else if (event->key() ==  Qt::Key_Left){
        actions[2] = 1;
    } else if ( event->key() ==  Qt::Key_Right){
        actions[3] = 1;
    } else if (event->key() == Qt::Key_Space){
        actions[4] = 1;
    }
}

void Game::keyReleaseEvent(QKeyEvent * event) {
    if (event->key() == Qt::Key_Up){
        actions[0] = 0;
    }  else if (event->key() ==  Qt::Key_Down){
        actions[1] = 0;
    }  else if (event->key() ==  Qt::Key_Left){
        actions[2] = 0;
    } else if ( event->key() ==  Qt::Key_Right){
        actions[3] = 0;
    } else if (event->key() == Qt::Key_Space){
        actions[4] = 0;
    }
}
// ВСТАВИТЬ В ИГРОВОЙ ЦИКЛ
/*
bool event(QEvent *event){
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = (QKeyEvent *)event;
            KeyboardState[keyEvent->key()] = true;
        }
        if (event->type() == QEvent::KeyRelease) {
            QKeyEvent *keyEvent = (QKeyEvent *)event;
            KeyboardState[keyEvent->key()] = false;
        }
        return QWidget::event(event);
    }
*/

/*
//обработка нажатий клавиатуры
void Game::keyPressEvent(QKeyEvent *event)
{
    if(!pause){
 //#if define DEBUG   qDebug() << "My Player do smth";
    if(event->key() == Qt::Key_Up) {
       //myIgrok1->setPos( myIgrok1->x(), myIgrok1->y()-10);
        actions[0] = 1;
    }
    else if(event->key() == Qt::Key_Left) {
        if( myIgrok1->pos().x() > 0){
        //myIgrok1->setPos( myIgrok1->x()-10, myIgrok1->y());
        actions[1] = 1;
        }
    }
    else if(event->key() == Qt::Key_Right) {
       if( myIgrok1->pos().x()+ myIgrok1->rect().width() < scene->width()){
             //myIgrok1->setPos( myIgrok1->x()+10, myIgrok1->y());
        actions[2] = 1;
       }
    }
    else if(event->key() == Qt::Key_Down) {
             //myIgrok1->setPos( myIgrok1->x(), myIgrok1->y()+10);
        actions[3] = 1;
    }
    else if (event->key() == Qt::Key_Space ) {
        //myIgrok1->fire();
        actions[4] = 1;
//        Bullet * bullet1 = new Bullet();
//        bullet1->setPos( myIgrok1->x()+ myIgrok1->rect().width()/2, myIgrok1->y());
//        bullet1->setRotation(myIgrok1->rotation());
//        scene->addItem(bullet1);
//        BulletList.push_back(bullet1);

    }else if(event->key() == Qt::Key_P)
        {
            gamePause();
        }
    }


}

//  обработка нажатия кнопок мышки
void Game::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event)
//    //create a bullet
//    Bullet * bullet1 = new Bullet();
//    bullet1->setPos( myIgrok1->x()+ myIgrok1->rect().width()/2, myIgrok1->y());
//    bullet1->setRotation(myIgrok1->rotation());
//    scene->addItem(bullet1);
//    BulletList.push_back(bullet1);
}

// ИСРАВИТЬ!!!!


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
*/

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

//  игровая пауза / не работает пауза таймеров!!!
void Game::gamePause()
{
       pause = 1;
       //enemy->stop();

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

// вращение за мышкой
inline void Game::slotMyPlayerMouse()
{
    myIgrok1->setRotation(angleToTarget);
    actions[5] = myIgrok1->rotation();
//    if (actions[0] == 1)
//        myIgrok1->setPos( myIgrok1->x(), myIgrok1->y()-1);
//    if (actions[1] == 1)
//        myIgrok1->setPos( myIgrok1->x(), myIgrok1->y()+1);
//    if (actions[2] == 1)
//        myIgrok1->setPos( myIgrok1->x()-1, myIgrok1->y());
//    if (actions[3] == 1)
//        myIgrok1->setPos( myIgrok1->x()+1, myIgrok1->y());
    //if (actions[4] == 1)

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

