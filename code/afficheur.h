#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include "includers.h"

class afficheur: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    afficheur(int nouvelleValeur = 0, QGraphicsItem* parent = nullptr);

public slots:
    void changerValeur(int newValue);
    void increment();

private:
    int valeur;
    QString texte;
    QGraphicsTextItem* valeurAffichee;
};

#endif // AFFICHEUR_H
