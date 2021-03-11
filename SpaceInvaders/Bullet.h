#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
//če hočeš uporabljati signale in reže mora biti klas izpeljan iz QObject
#include<QObject>

class Bullet: public QObject,public QGraphicsPixmapItem{
    //moraš dodati Q_Object MAKRO za reže in signale
    Q_OBJECT
public:
    Bullet();
    //reže
public slots:
    void move();
};

#endif // BULLET_H
