#ifndef ZONEJEU_H
#define ZONEJEU_H

#include <includers.h>

class zoneJeu: public QGraphicsRectItem
{
public:
    zoneJeu(QGraphicsItem* parent = nullptr);
public slots:
    void update();
};

#endif // ZONEJEU_H
