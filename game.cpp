#include <game.h>
#include <myplayer.h>
#include <bullet.h>
#include <enemy.h>
#include <QTimer>
#include <QFont>
#include <QGraphicsScene>
#include <score.h>
#include <health.h>

Game::Game(QWidget * parent)
{
   scene = new QGraphicsScene();
   scene->setSceneRect(0,0,380,780);
   setScene(scene);
   setFixedSize(400,800);

   myIgrok = new MyPlayer();
   myIgrok->setRect(0,0,40,40);
   myIgrok->setPos(200,400);
   //add item on the scene
   scene->addItem(myIgrok);
   //MAKE PLAYER FOCUS
   myIgrok->setFlag(QGraphicsItem::ItemIsFocusable);
   myIgrok->setFocus();

   score = new Score();
   scene->addItem(score);
   score->show();


   health = new Health();
   health->setHealth(10);
   scene->addItem(health);
   health->setPos(0,25);
   health->showHealth();
    //score->increaseScore();

   //создание элемента на сцене




    // spawn enemies
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),myIgrok,SLOT(spawn()));
    timer->start(2000);

    //this->backgroundBrush(QBrush::setTextureImage())
    show();
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
