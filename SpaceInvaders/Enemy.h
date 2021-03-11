#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
//če hočeš uporabljati signale in reže mora biti klas izpeljan iz QObject
#include<QObject>

class Enemy: public QObject,public QGraphicsPixmapItem{
    //moraš dodati Q_Object MAKRO za reže in signale
    Q_OBJECT
public:
    Enemy();
    //reže
public slots:
    void move();
};


#endif // ENEMY_H
