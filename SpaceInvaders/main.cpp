#include <QApplication>
#include "Game.h"
#include <QDebug>

Game * game;

int main(int argc, char*argv[]){
    QApplication a(argc,argv);
    game = new Game;
    game->prikazMainMenu();

    return a.exec();
}
