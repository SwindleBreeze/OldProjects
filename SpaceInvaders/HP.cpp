#include "HP.h"
#include <QFont>
#include <QtDebug>
Health::Health(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    // inicializacija HP na 3
    health = 3;

    //nariši text
    setFont(QFont("times",16));
    setPlainText(QString("Health: ") + QString::number(health));
    setDefaultTextColor(Qt::red);
    // size okna je 700,600
    setPos(130,545);
}

void Health::decrease()
{
    health--;
    setPlainText(QString("Health: ") + QString::number(health));
}

int Health::getHealth()
{
    return health;
}

void Health::setHealth(int n)
{
    health=n;
    setPlainText(QString("Health: ") + QString::number(health));
}
