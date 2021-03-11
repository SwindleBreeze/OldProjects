#include "Bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>
#include "Enemy.h"
#include "Game.h"
#include <EnemyBullet.h>

extern Game * game; // obstaja zunanji globalni objekt "game" ki je GAME pointer

Bullet::Bullet()
{
    // narisali metek
    setPixmap(QPixmap(":/images/bullet.png"));
    // position nastavil že v shoot button v SpacheShip

    //povezi reže
    QTimer *čas = new QTimer();
    //prvi argument je objekt signala ki zelis povezati
    //drugi argument je signal
    //tretji argument je objekt katerega režo hočemo povezat
    //cetrti argument je reža
    //poveže timer z move režo ki smo naredili v bullet.h(metek premika)
    connect(čas,SIGNAL(timeout()),this,SLOT(move()));
    //signal pošlje na 50 ms
    čas->start(50);
}

void Bullet::move()
{
    // pogled ce se zabije
    QList<QGraphicsItem *>colliding_items=collidingItems();
    for(int i=0,n=colliding_items.size();i<n;i++)
    {
        if(typeid(*(colliding_items[i]))==typeid(Enemy))
        {   //increase score
            game->score->increase();

            //izbirse
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            //delete from heap
            delete colliding_items[i];
            delete this;
            return;
        }

    }

    // premik metka gor
    setPos(x(),y()-10);
    if(pos().y()<0)
    {
        scene()->removeItem(this);
        delete this;
        qDebug()<<"Metek je bil izbrisan";
    }
}
