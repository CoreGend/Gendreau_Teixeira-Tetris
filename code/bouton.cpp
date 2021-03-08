#include "bouton.h"

/* constructeur */
bouton::bouton(QString nom, int x, int y,QGraphicsItem* parent): QGraphicsRectItem(parent)
{
    setRect(0,0,x,y);

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

/* gère action lorsque l'utilisateur clique sur le bouton*/
void bouton::mousePressEvent(QGraphicsSceneMouseEvent *event) { emit clicked(); }

/*  gère ce qu'il se passe lorsque le curseur passe sur la zone puis la quitte :
    change la couleur du fond*/
void bouton::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(174,242,242));
    setBrush(brush);
}

void bouton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(226,226,226,127));
    setBrush(brush);
}
