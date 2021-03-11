#include "Enemy.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include "EnemyBullet.h"
#include "Game.h"
#include "BUttons.h"

extern Game *game;
Enemy::Enemy()
{
    // narisali enemy
    setPixmap(QPixmap(":/images/saucer2b"));

    //povezi reže
    QTimer *čas = new QTimer();
    //prvi argument je objekt signala ki zelis povezati
    //drugi argument je signal
    //tretji argument je objekt katerega režo hočemo povezat
    //cetrti argument je reža
    //poveže timer z move režo ki smo naredili v bullet.h(metek premika)
    connect(čas,SIGNAL(timeout()),this,SLOT(move()));
    //signal pošlje na 50 ms
    čas->start(1000);
}

std::string setting="right";

void Enemy::move()
{
    // premika sovražnika dol levo/desno
    setPos(x(),y()+5);
    if(pos().y()<0)
    {
        scene()->removeItem(this);
        delete this;
    }
    if(pos().y()>game->player->y())
    {
        game->prikazContinue();
    }

}
