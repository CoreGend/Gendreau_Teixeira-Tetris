#ifndef FENETREJEU_H
#define FENETREJEU_H

#include "includers.h"
#include "piece.hpp"
#include "bouton.h"

class fenetreJeu: public QGraphicsView
{
// constructeurs
public:
    fenetreJeu(QWidget* parent = nullptr);

// slots
public slots:

// signaux
signals:

// Ã©lÃ©ments propres Ã  la fenÃªtre
private:
    QGraphicsScene* scene;  //la scÃ¨ne qui sera utilisÃ©e
    QGraphicsView* vue;     //la vue qui sera liÃ©e Ã  la scÃ¨ne
//    piece* pieceActive;     //la piece qui sera active

    bouton* quitter;   //le bouton quitter
//    QGraphicsTextItem* scoreText;      //label score
//    QLCDNumber* score;      //afficheur score
//    QGraphicsTextItem* nbLigneText;    //label afficheur du nombre de lignes effacÃ©es
//    QLCDNumber* nbLigne;    //afficheur nombre lignes effacÃ©es
//    QGraphicsTextItem* difficulteText; //label difficultÃ©
//    QLCDNumber* difficulte; //afficheur difficulte
};

#endif // FENETREJEU_H
