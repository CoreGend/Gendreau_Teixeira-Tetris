#ifndef JEU_H
#define JEU_H

#include "includers.h"
#include "tableau.hpp"
#include "afficheur.h"
#include "piece.hpp"

class jeu:public QGraphicsView{
    Q_OBJECT
public:
    jeu(QWidget* parent = nullptr);

    void afficherFenetreJeu();
    piece genererPiece();
    void effacerLigne();
    void iteration();
    void afficherTableau();
    void keyPressEvent(QKeyEvent* event);
    void newDiff();

    QGraphicsScene* scene;

public slots:
    void start();
    void new_tick();


private :
    int iter = 0, scoreValue=0, nbLigneEffacees = 0, enJeu = 0, diff = 1, numDiff;
    afficheur* score;
    afficheur* nbLigne;
    afficheur* difficulte;
    tableau* tab;
    piece pieceActive;
    QGraphicsRectItem* pieceAffichees[220];
};

#endif // JEU_H
