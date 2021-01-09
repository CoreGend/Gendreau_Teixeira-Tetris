#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include "includers.h"

/*  zone rectangulaire avec un nombre affiché à l'intérieur */
class afficheur: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    afficheur(long unsigned int nouvelleValeur = 0, QGraphicsItem* parent = nullptr);
/*  Il n'est pas nécessaire de faire les destructeurs puisque l'objet
    est un objet Qt, qui gère lui-même la destruction de ses objets à
    la fermeture d'un programme */

public slots:
    void changerValeur(long unsigned int newValue);

private:
    long unsigned int valeur;
    QString texte;
    QGraphicsTextItem* valeurAffichee;
};

#endif // AFFICHEUR_H
