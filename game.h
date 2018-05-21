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

#include "enemy.h"
#include "myplayer.h"

class Game : public QGraphicsView
{
public:
    Game(QWidget * parent = 0);
    MyPlayer * myIgrok;
    Score * score;
    Health * health;
    QGraphicsScene * scene;

private:

    void closeEvent(QCloseEvent * event);
};


#endif // GAME_H
