#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "SpaceShip.h"
#include "Score.h"
#include "HP.h"
#include "Enemy.h"
#include <QMouseEvent>
#include <QObject>
#include "EnemyBullet.h"
#include "EnemyMarker.h"

class Game : public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;
    SpaceShip *player;
    Score *score;
    Health *health;
    Enemy *enemy;
    EnemyBullet *enemymetek;
    EnemyMarker *mark;
    void prikazMainMenu();
    void prikazContinue();
private:
    QMediaPlayer * Background;
public slots:
    void zazeni();
    void zapri();
};

#endif // GAME_H
