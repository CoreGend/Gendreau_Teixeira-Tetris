#include "afficheur.h"

afficheur::afficheur(int nouvelleValeur, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    setRect(0,0,200,50);

    valeur = nouvelleValeur;
    texte.setNum(valeur);

    valeurAffichee = new QGraphicsTextItem(texte, this);
    int posx = rect().width()/2 - valeurAffichee->boundingRect().width()/2;
    int posy = rect().height()/2 - valeurAffichee->boundingRect().height()/2;
    valeurAffichee->setPos(posx, posy);
}

void afficheur::changerValeur(int newValue)
{
    valeur = newValue;
    texte.setNum(newValue);
    valeurAffichee->setPlainText(texte);
    qDebug() << "Nouvelle valeur : " << valeur;
}

void afficheur::increment()
{
    valeur+=1;
    changerValeur(valeur);
}
