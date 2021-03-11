#ifndef HP_H
#define HP_H

#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{
public:
    Health(QGraphicsItem * parent=0);
    void decrease();
    int getHealth();
    void setHealth(int n);
private:
    int health;
};

#endif // HP_H
