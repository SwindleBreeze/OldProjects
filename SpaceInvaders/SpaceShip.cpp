#include "SpaceShip.h"
#include "Bullet.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QElapsedTimer>
#include <QtDebug>
#include <Game.h>
#include "EnemyBullet.h"

extern Game * game;
SpaceShip::SpaceShip(QGraphicsItem *parent)
{
   zvokmetka= new QMediaPlayer();
   zvokmetka->setMedia(QUrl("qrc:/sound/shoot.wav"));
}

void SpaceShip::keyPressEvent(QKeyEvent *event)
{
    QElapsedTimer *time = new QElapsedTimer;
    time->start();
    if(event->key()==Qt::Key_Left)
    {
        if(pos().x() > 0 )
        {
            setPos(x()-10,y());
        }
    }
    else
    {
        if(event->key()==Qt::Key_Right)
        {
            if(pos().x()+50 < 700)
            {
              setPos(x()+10,y());
            }

        }
        else if(event->key()==Qt::Key_Space)
        {
            // naredi metek
            Bullet *metek = new Bullet();
            metek->setPos(x()+20,y());
            scene()->addItem(metek);

            //predvajaj zvok metka
            if(zvokmetka->state()==QMediaPlayer::PlayingState)
            {
                zvokmetka->setPosition(0);
            }
            else if(zvokmetka->state()==QMediaPlayer::StoppedState)
            {
                zvokmetka->play();
            }
        }
    }
    if(event->key()==Qt::Key_Enter)
    {
        game->close();
        game=new Game;
        game->show();
    }
}

void SpaceShip::spawn()
{
    //ustvari metek;
    EnemyBullet * metek = new EnemyBullet();
    scene()->addItem(metek);
}
