#include <game.h>
#include <myplayer.h>
#include <bullet.h>
#include <enemy.h>
#include <QTimer>
#include <QFont>
#include <QGraphicsScene>
#include <score.h>
#include <health.h>



void Game::spawn()
{
    Enemy * enemy = new Enemy;
    scene->addItem(enemy);
}


Game::Game(QWidget * parent)
{
   scene = new QGraphicsScene();
   scene->setSceneRect(0,0,800,800);
   setScene(scene);
   setFixedSize(810,810);

   setMouseTracking(true);
   myIgrok = new MyPlayer();
   myIgrok->setRect(0,0,50,30);
   myIgrok->head->setRect(0,0,20,20);
   myIgrok->pistol->setRect(0,0,8,30);

   myIgrok->setPos(200,400);
   //add item on the scene
   scene->addItem(myIgrok);
   scene->addItem(myIgrok->head);
   scene->addItem(myIgrok->pistol);
   //MAKE PLAYER FOCUS
   myIgrok->setFlag(QGraphicsItem::ItemIsFocusable);
   myIgrok->setFocus();

    spawnEnemys();
   /*
   score = new Score();
   scene->addItem(score);
   score->show();
   health = new Health();
   scene->addItem(health);
   health->setPos(0,25);
   */


    show();
}





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

// spawn enemies
void Game::spawnEnemys()
{
    enemy = new QTimer();
    QObject::connect(enemy,SIGNAL(timeout()),this,SLOT(spawn()));
    enemy->start(2000);
}

void Game::keyPressEvent(QKeyEvent *event)
{

 //#if define DEBUG   qDebug() << "My Player do smth";
    if(event->key() == Qt::Key_Up) {
       myIgrok->setPos( myIgrok->x(), myIgrok->y()-10);
    }
    else if(event->key() == Qt::Key_Left) {
        if( myIgrok->pos().x() > 0){
        myIgrok->setPos( myIgrok->x()-10, myIgrok->y());
        }
    }
    else if(event->key() == Qt::Key_Right) {
       if( myIgrok->pos().x()+ myIgrok->rect().width() < scene->width()){
             myIgrok->setPos( myIgrok->x()+10, myIgrok->y());
        }
    }
    else if(event->key() == Qt::Key_Down) {
             myIgrok->setPos( myIgrok->x(), myIgrok->y()+10);
    }
    else if (event->key() == Qt::Key_Space ) {
        myIgrok->fire();
//#if define DEBUG     qDebug() << "Bullet create";
    }
}
/*
void Game::slotMyPlayerMouse(QPointF point)
{
    // Определяем расстояние до цели
    target = point;
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
    // Угол поворота в направлении к цели
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    // В Зависимости от того, слева или справа находится Цель от Героя,
     // устанавливаем направление поворота Героя в данном тике таймера

    if (angleToTarget >= 0 && angleToTarget < Pi) {
        // Rotate left
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        // Rotate right
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
}*/


void Game::mousePressEvent(QMouseEvent *event){
    //create a bullet
    Bullet * bulletc = new Bullet();
    bulletc->setPos(event->pos());
    bulletc->setRotation(-90);
    scene->addItem(bulletc);

}


void Game::mouseMoveEvent(QMouseEvent *event){

       myIgrok->setPos( event->pos().x()-20,event->pos().y()-20);
}

void Game::closeEvent(QCloseEvent *event)
{
    event->ignore();
   // MainMenu * newMenu = new MainMenu();
    //newMenu->show();
    this->close();
    delete this;
    event->accept();
}
