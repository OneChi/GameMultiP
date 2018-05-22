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
   scene->setSceneRect(0,0,380,780);
   setScene(scene);
   setFixedSize(400,800);


   setMouseTracking(true);
   myIgrok = new MyPlayer();
   myIgrok->setRect(0,0,40,40);
   myIgrok->setPos(200,400);
   //add item on the scene
   scene->addItem(myIgrok);
   //MAKE PLAYER FOCUS
   myIgrok->setFlag(QGraphicsItem::ItemIsFocusable);
   myIgrok->setFocus();


   /*
   score = new Score();
   scene->addItem(score);
   score->show();
   health = new Health();
   scene->addItem(health);
   health->setPos(0,25);
   */



    //score->increaseScore();

   //создание элемента на сцене




    // spawn enemies
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(spawn()));
    timer->start(2000);

    //this->backgroundBrush(QBrush::setTextureImage())
    show();
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


void Game::mousePressEvent(QMouseEvent *event){
    //create a bullet
    Bullet * bulletc = new Bullet();
    bulletc->setPos(event->pos());
    bulletc->setRotation(40);
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
