#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

// dodeli key evenet ki dovoli klik na tikovnici
class SpaceShip:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    SpaceShip(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
public slots:
    void spawn();
private:
    QMediaPlayer * zvokmetka;
};

#endif // MYRECT_H
