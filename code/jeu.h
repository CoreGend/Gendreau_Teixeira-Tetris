#ifndef JEU_H
#define JEU_H

#include "includers.h"
#include "tableau.hpp"
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

    QGraphicsScene* scene;

public slots:
    void start();
    void new_tick();


private :
    int iter = 0;
    tableau* tab;
    piece pieceActive;
    QGraphicsRectItem* pieceAffichees[220];
};

#endif // JEU_H
