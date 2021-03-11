#include "BUttons.h"
#include <QBrush>
#include <QGraphicsTextItem>

Button::Button(QString name, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    //narisi rectangle
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);

    //narises text
    text = new QGraphicsTextItem(name,this);
    int xPos=rect().width()/2- text->boundingRect().width()/2;
    int yPos=rect().height()/2-text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    //respond na hover
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();

}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    // zamenjam barvo
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // zamenjam barvo
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
}
