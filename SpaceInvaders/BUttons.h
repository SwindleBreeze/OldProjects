#ifndef BUTTONS_H
#define BUTTONS_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>



class Button:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    //konstruktor
    Button (QString name, QGraphicsItem* parent=NULL);

    //metode
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
private:
    QGraphicsTextItem* text; // tekst na buttonu
};

#endif // BUTTONS_H
