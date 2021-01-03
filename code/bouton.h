#ifndef BOUTON_H
#define BOUTON_H

#include "includers.h"

class bouton: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    bouton(QString nom, QGraphicsItem* parent=nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

signals:
    void clicked();

private:
    QGraphicsTextItem* text;
};

#endif // BOUTON_H
