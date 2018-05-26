#include <game.h>
#include <myplayer.h>
#include <bullet.h>
#include <enemy.h>
#include <QTimer>
#include <QLineF>
#define _USE_MATH_DEFINES
#include <QGraphicsPixmapItem>
#include <qmath.h>
#include "score.h"
#include "myevent.h"
#include <QFont>
#include <QGraphicsScene>
#include <score.h>
#include <health.h>


qreal angleToTarget  = 0;
//  CONSTRUCTOR
Game::Game(QWidget * parent)
{
    Q_UNUSED(parent)
   scene = new QGraphicsScene();
   scene->setSceneRect(0,0,800,800);
   mouse = new QTimer();
   setScene(scene);
   setFixedSize(810,810);
   setMouseTracking(true);
   enemy = new QTimer();
   QObject::connect(enemy,SIGNAL(timeout()),this,SLOT(spawn()));
   QObject::connect(mouse,SIGNAL(timeout()),this,SLOT(slotMyPlayerMouse()));
    mouse->start(2);

   gameSet();



   /*
   score = new Score();
   scene->addItem(score);
   score->show();
   health = new Health();
   scene->addItem(health);
   health->setPos(0,25);
   */


    //show();
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
    Enemy * enemy = new Enemy;
    scene->addItem(enemy);
}

//  инициализация игрока 1
void Game::setPlayer1()
{
    myIgrok1 = new MyPlayer();
    myIgrok1->setRect(0,0,50,30);
    myIgrok1->head->setRect(0,0,20,20);
    myIgrok1->pistol->setRect(0,0,8,30);
}

//  инициализация игрока 2
void Game::setPlayer2()
{
    myIgrok2 = new MyPlayer();
    myIgrok2->setRect(0,0,50,30);
    myIgrok2->head->setRect(0,0,20,20);
    myIgrok2->pistol->setRect(0,0,8,30);

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
    myIgrok1->setPos(200,400);
    //add item on the scene
    scene->addItem(myIgrok1);
    scene->addItem(myIgrok1->head);
    scene->addItem(myIgrok1->pistol);
    //MAKE PLAYER FOCUS



    myIgrok1->setFlag(QGraphicsItem::ItemIsFocusable);
    myIgrok1->setFocus();

     spawnEnemys();
}

//  игровая пауза / не работает пауза таймеров!!!
void Game::gamePause()
{
       pause = 1;
       enemy->stop();

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
        myIgrok1->fire();
//#if define DEBUG     qDebug() << "Bullet create";

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
    Bullet * bulletc = new Bullet();
    bulletc->setPos(myIgrok1->pos());
    bulletc->setRotation(myIgrok1->rotation());
    scene->addItem(bulletc);

}

void Game::mouseMoveEvent(QMouseEvent *event) {

    QLineF lineToTarget(QPointF(myIgrok1->pos().x(), myIgrok1->pos().y()), QPointF(event->posF().x(),event->posF().y()));
//qreal
    angleToTarget = acos(lineToTarget.dx() / lineToTarget.length());

    if (lineToTarget.dy() > 0){
        if (angleToTarget >= 0 && angleToTarget < M_PI) {
            // Rotate left
         myIgrok1->setRotation((angleToTarget * 180) /M_PI+90);
        } else if (angleToTarget <= M_2_PI && angleToTarget > M_PI) {
            // Rotate right
         myIgrok1->setRotation((angleToTarget - M_2_PI )* (-180) /M_PI+90);
        }
    } else {
        if (angleToTarget >= 0 && angleToTarget < M_PI) {
            // Rotate left
         myIgrok1->setRotation(((angleToTarget * 180) /M_PI)*-1+90);
        } else if (angleToTarget <= M_2_PI && angleToTarget > M_PI) {
            // Rotate right
         myIgrok1->setRotation(((angleToTarget - M_2_PI )* (-180) /M_PI)*-1+90);
        }

    }
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

//  ===
void Game::keyPressW(QKeyEvent *event)
{
    if(event->key() == Qt::Key_1) {

            myIgrok1->setPos( myIgrok1->x(), myIgrok1->y()-10);

      }
}

//QPointF point !!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
void Game::slotMyPlayerMouse()
{

//    QLineF lineToTarget(QPointF(myIgrok1->pos().x(), myIgrok1->pos().y()), target->toPoint());

//    qreal angleToTarget = acos(lineToTarget.dx() / lineToTarget.length());

//    if (lineToTarget.dy() > 0){
//        if (angleToTarget >= 0 && angleToTarget < M_PI) {
//            // Rotate left
//         myIgrok1->setRotation((angleToTarget * 180) /M_PI+90);
//        } else if (angleToTarget <= M_2_PI && angleToTarget > M_PI) {
//            // Rotate right
//         myIgrok1->setRotation((angleToTarget - M_2_PI )* (-180) /M_PI+90);
//        }
//    } else {
//        if (angleToTarget >= 0 && angleToTarget < M_PI) {
//            // Rotate left
//         myIgrok1->setRotation(((angleToTarget * 180) /M_PI)*-1+90);
//        } else if (angleToTarget <= M_2_PI && angleToTarget > M_PI) {
//            // Rotate right
//         myIgrok1->setRotation(((angleToTarget - M_2_PI )* (-180) /M_PI)*-1+90);
//        }

//    }
}
//myIgrok1->translate(myIgrok1->rect().height()/2,myIgrok1->rect().width()/2);
