#include "bouton.h"

bouton::bouton(QString nom, QGraphicsItem* parent): QGraphicsRectItem(parent)
{
    setRect(0,0,200,50);

    //déco
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(226,226,226,127));
    setBrush(brush);

    //met le texte
    text = new QGraphicsTextItem(nom, this);
    int xpos = rect().width()/2 - text->boundingRect().width()/2;
    int ypos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xpos, ypos);

    setAcceptHoverEvents(true);
}

void bouton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void bouton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //change la couleur
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(174,242,242));
    setBrush(brush);
}

void bouton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //remet la couleur normale
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(226,226,226,127));
    setBrush(brush);
}
