#ifndef ENEMYMARKER_H
#define ENEMYMARKER_H

#include <QGraphicsRectItem>
//če hočeš uporabljati signale in reže mora biti klas izpeljan iz QObject
#include<QObject>

class EnemyMarker: public QObject,public QGraphicsRectItem{
    //moraš dodati Q_Object MAKRO za reže in signale
    Q_OBJECT
public:
    EnemyMarker();
    //reže
public slots:
    void move();
};

#endif // ENEMYMARKER_H
