#include "EnemyBullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <QList>
#include "Enemy.h"
#include "Game.h"
#include <stdlib.h>
#include "HP.h"
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QKeyEvent>
#include "SpaceShip.h"
#include <stdlib.h>
#include <QtDebug>
#include <QGraphicsPixmapItem>
#include <Bullet.h>

extern Game * game; // obstaja zunanji globalni objekt "game" ki je GAME pointer

int i=0;
EnemyBullet::EnemyBullet()
{
    // narisali metek
    qDebug()<<"Spawned enemybullet"<<endl;
    setPixmap(QPixmap(":/images/bullet.png"));
    setPos(game->player->x()+20,game->mark->y()+20);
    setTransformOriginPoint(4.5,9.5);
    setRotation(180);
    increase();
    //povezi reže
    QTimer *čas = new QTimer(this);
    //prvi argument je objekt signala ki zelis povezati
    //drugi argument je signal
    //tretji argument je objekt katerega režo hočemo povezat
    //cetrti argument je reža
    //poveže timer z move režo ki smo naredili v bullet.h(metek premika)
    connect(čas,SIGNAL(timeout()),this,SLOT(move()));
    //signal pošlje na 50 ms
    čas->start(25);
    return;
}

void EnemyBullet::increase()
{
    meteky+=5;
}

int EnemyBullet::returny()
{
    return meteky;
}
void EnemyBullet::move()
{
    QGraphicsTextItem *Game_over= new QGraphicsTextItem;
    QGraphicsTextItem *HIScore = new QGraphicsTextItem;

    // pogled ce se zabije
    QList<QGraphicsItem *>colliding_items=collidingItems();
    for(int i=0,n=colliding_items.size();i<n;i++)
    {
        if(typeid(*(colliding_items[i]))==typeid(SpaceShip))
        {
            //izbirse
            scene()->removeItem(this);
            game->health->decrease();
            if(game->health->getHealth()==0)
            {
                game->prikazContinue();
            }
            //delete from heap
            delete this;
            return;
        }
    }
    // premik metka dol
    setPos(x(),y()+10);
    if(pos().y()>600)
    {
        scene()->removeItem(this);
        delete this;
        qDebug()<<"Metek je bil izbrisan";
    }
    i=game->score->getScore();
    if(i%3600==0)
    {
        delete this;
        return;
        i++;
    }
}
