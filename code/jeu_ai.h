#ifndef JEU_AI_H
#define JEU_AI_H

#include "jeu.h"
#include "includers.h"


class jeu_ai : public jeu
{
    /* Constructeur */
    public:
        jeu_ai(QWidget* parent = nullptr);

    /* Fonction ai */
        void recherche_moves_ai(int prev_nb_trous);
        int nb_trous(tableau* tab, bool eff);
        int calcul_poids(piece piece, tableau* t, int prev_nb_trous);
        
    public slots:
        void new_tick();
        void start();


    /* Attributs ai */
    protected:
        std::vector<int> ai_move; //Mouvements que va suivre l'ai : -1, 0, 1 pour gauche, tourner et droite
        int i_move = 0;     //Indice du prochain movement dans le vecteur ci dessus.
        int iter_ai = 0;    //Comme l'autre iter, mais pour les mouvements de l'ai
        piece pieceActive_fantome;  //Pour voir les positions d'arrêts à l'avances
        tableau* tab_fantome;       //Pareil
        
};

#endif // JEU_AI_H