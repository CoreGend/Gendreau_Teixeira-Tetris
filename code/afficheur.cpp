#include "afficheur.h"

/* constructeur */
afficheur::afficheur(long unsigned int nouvelleValeur, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    setRect(0,0,200,50);

    QFont font; font.setStretch(QFont::Expanded);
    int tailleDefaut = font.pointSize();
    font.setPointSize(tailleDefaut+8);

    valeur = nouvelleValeur;
    texte.setNum(valeur);

    valeurAffichee = new QGraphicsTextItem(texte, this);
    valeurAffichee->setFont(font);
    int posx = rect().width()/2 - valeurAffichee->boundingRect().width()/2;
    int posy = rect().height()/2 - valeurAffichee->boundingRect().height()/2;
    valeurAffichee->setPos(posx, posy);
}

/* changement de la valeur affichée */
void afficheur::changerValeur(long unsigned int newValue)
{
    valeur = newValue;
    texte.setNum(newValue);
    valeurAffichee->setPlainText(texte);

    int posx = rect().width()/2 - valeurAffichee->boundingRect().width()/2;
    int posy = rect().height()/2 - valeurAffichee->boundingRect().height()/2;
    valeurAffichee->setPos(posx, posy);
}
