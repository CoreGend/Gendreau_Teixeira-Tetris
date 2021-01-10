#ifndef JEU_H
#define JEU_H

#include "includers.h"
#include "tableau.hpp"
#include "afficheur.h"
#include "piece.hpp"

class jeu:public QGraphicsView{
    Q_OBJECT
public:
    /* constructeur */
    jeu(QWidget* parent = nullptr);

    /* fonctions */
    void afficherFenetreJeu();
    piece genererPiece();
    void effacerLigne();
    void afficherTableau(tableau* loc_tab, QGraphicsRectItem** listePieces);
    void keyPressEvent(QKeyEvent* event);
    void newDiff();
    void insertText(QString text);
    void removeText();
    void afficherBuffer();

public slots:
    void start();
    void new_tick();
    void pauseGame();


private :
    /*  éléments qui peuvent être modifiés en cours de partie */
    int scoreValue=0, //score actuel
        nbLigneEffacees = 0,//nombre de lignes effacées
        iter = 0,   //nombre de rafraichissement de la fenetre - réinitialisé lorsque le compteur atteint numDiff
        diff = 1,   //difficulté de jeu
        numDiff;    //nombre de rafraichissement de l'image avant de descendre une pièce automatiquement
    bool    enJeu = false,//faux tant que le timer n'est pas initialisé, évite de l'activer plusieurs fois
            pauseActive = false,
            finPartie = false;//faux tant que la partie n'est pas finie
    afficheur* score;
    afficheur* nbLigne;
    afficheur* difficulte;
    tableau* tab; tableau* buff;
    piece pieceActive; piece buffer[2];
    QGraphicsRectItem* pieceAffichees[220];
    QGraphicsRectItem* pieceBuffer[18];
    QGraphicsTextItem* inGameText;
    QGraphicsRectItem* inGameTextZone;
    QGraphicsScene* scene;
};

#endif // JEU_H
