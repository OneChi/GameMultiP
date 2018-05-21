#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>

#include <enemy.h>
#include <game.h>
#include <myplayer.h>
//LINUX
#include <sys/socket.h>
#include <netinet/ether.h>

//MainMenu * game;
Game * myGame;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    game = new MainMenu;
//    game->show();
//    game->maingame->score->increaseScore();
    myGame = new Game();
    myGame->show();

    return a.exec();
}

