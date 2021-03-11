#include "EnemyMarker.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include "EnemyBullet.h"
#include "Game.h"

extern Game *game;
EnemyMarker::EnemyMarker()
{
    // narisali enemy
    setRect(0,0,20,2);

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

void EnemyMarker::move()
{
    // premika sovražnika dol levo/desno
    setPos(game->player->x()+50,y()+5);
    if(pos().y()+rect().height()<0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
