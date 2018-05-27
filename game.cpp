

#include <stdlib.h>

#include <QTimer>
#include <QLineF>
#define _USE_MATH_DEFINES
//#include <QGraphicsPixmapItem>
#include <qmath.h>
//#include <QFont>
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
Game::Game(QWidget * parent)
{
    Q_UNUSED(parent)
   scene = new QGraphicsScene();
   scene->setSceneRect(0,0,800,800);
   mouse = new QTimer();
   target= new QPointF();
   setScene(scene);
   setFixedSize(810,810);
   setMouseTracking(true);
   enemy = new QTimer();
   QObject::connect(enemy,SIGNAL(timeout()),this,SLOT(spawn()));
   QObject::connect(mouse,SIGNAL(timeout()),this,SLOT(slotMyPlayerMouse()));
    mouse->start(2);

   gameSet();

    // Play Background music


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


    Enemy * enemy = new Enemy();
    scene->addItem(enemy);
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
       enemy->stop();

}

void Game::gameSetTest()
{

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

// ИСРАВИТЬ!!!!
void Game::mouseMoveEvent(QMouseEvent *event) {
   //myIgrok->setPos( event->pos().x()-20,event->pos().y()-20);

    target->setX(event->pos().x());
    target->setY(event->pos().y());


    QLineF lineToTarget(QPointF(myIgrok1->pos().x(), myIgrok1->pos().y()), target->toPoint());
//qreal
    angleToTarget = acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() > 0){
        angleToTarget = (angleToTarget * 180) /M_PI+90;
    }else{
        angleToTarget = (angleToTarget * 180) /M_PI*-1+90;
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


//QPointF point !!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
void Game::slotMyPlayerMouse()
{

    myIgrok1->setRotation(angleToTarget);


   /* if (angleToTarget-myIgrok1->rotation() > 0 && angleToTarget-myIgrok1->rotation() < 180){
    myIgrok1->setRotation(myIgrok1->rotation() + 1);
  }else{
     myIgrok1->setRotation(myIgrok1->rotation() - 1);
  }*/

  /*if (angleToTarget >= 0 && angleToTarget < 90) {
      // Rotate left
      myIgrok1->setRotation(myIgrok1->rotation() + 1);
  } else if (angleToTarget-myIgrok1->rotation() <= 180 && angleToTarget-myIgrok1->rotation() > 90) {
      // Rotate right
      myIgrok1->setRotation(myIgrok1->rotation() - 1);
  }*/

}
