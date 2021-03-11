#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QGraphicsPixmapItem>
//če hočeš uporabljati signale in reže mora biti klas izpeljan iz QObject
#include<QObject>

class EnemyBullet: public QObject,public QGraphicsPixmapItem{
    //moraš dodati Q_Object MAKRO za reže in signale
    Q_OBJECT
private:
    int meteky=0;
public:
    EnemyBullet();
    void increase();
    int returny();
    //reže
public slots:
    void move();
};

#endif // ENEMYBULLET_H
