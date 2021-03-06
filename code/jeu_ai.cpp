#include "jeu_ai.h"
#include "includers.h"

/* Constructeur */
jeu_ai::jeu_ai(QWidget* parent): jeu(parent) {}

/* Lancement de jeu identique sauf pour la rotation de certaine pièces au début */
void jeu_ai::start(){
    tab = new tableau(22,10);
    buff = new tableau(2,9);
    removeText();

    pieceActive = piece(nombrePiece++);
    pieceActive._init_(tab);
    
    /* Pour l'ia : Rotation de la 1ère pièce si besoin */
    if (pieceActive.getnum_piece()==2 || pieceActive.getnum_piece()==3 || pieceActive.getnum_piece()==4)
    {
        pieceActive.rotation(tab);
        pieceActive.rotation(tab);
    }

    buffer[0] = piece(nombrePiece++);
    buffer[1] = piece(nombrePiece++);

    diff = 1; newDiff();

    afficherTableau(tab, pieceAffichees);
    afficherBuffer();

    if(enJeu == false)
    {
        QTimer* timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(new_tick()));
        timer->start(16);
        enJeu = true;
    }
    else
    {
        scoreValue = 0; score->changerValeur(scoreValue);
        nbLigneEffacees = 0; nbLigne->changerValeur(nbLigneEffacees);
        difficulte->changerValeur(diff);
        pauseActive = false;
        finPartie = false;
    }
}


int jeu_ai::nb_trous(tableau* tab, bool eff)
{
    /* Debugage :
    for (int j=3; j<7; j++)
    {
        (*tab)(0,j).setidentifiant(0);
        (*tab)(1,j).setidentifiant(0);
    }
    */

    int nb = 0;
    for (int j=0; j<(*tab).getlargeur(); j++)
    {
        int nb_vide = 0;
        std::vector<int> liste;
        for (int i=(*tab).gethauteur()-1; i>=0; i--)
        {
            if ((*tab)(i,j).getidentifiant() == 0) 
            {
                nb_vide++;
                liste.push_back(i);
            }
            else 
            {
                nb += nb_vide;
                nb_vide = 0;
                if (eff) liste.clear();
            }
        }
    }
    return nb;
}

int jeu_ai::calcul_poids(piece piece, tableau* t, int prev_nb_trous)
{
    int poids = 0;
    int k = (*t).reconnaissance_ligne();
    bool eff = false;
    while (k != -1)
    {
        poids -= 30;
        (*t).effacement_ligne(k);
        k = (*t).reconnaissance_ligne();
        eff = true;
    }

    int nb_t = nb_trous(t, eff);
    poids += 10*abs(nb_t - prev_nb_trous);   //constante expérimentale, pour que les trous soient plus désavantagés que la hauteur d'arrivée.
    int hauteur_max = 0;
    for (part_piece pp : piece.getpieces())
        if (hauteur_max < (*t).gethauteur() - pp.getligne()-1)
            hauteur_max = (*t).gethauteur() - pp.getligne()-1;
    poids += hauteur_max*3;

    return poids;
}


/* Algo de recherche de mouvement de l'ai */
void jeu_ai::recherche_moves_ai(int prev_nb_trous)
{
    int nb_pos_moves = 44;
    std::vector<std::vector<int>> possible_moves(nb_pos_moves);   //vecteur contenant tous les déplacements possibles en commencant par le poids de celle-ci (0 par défaut).
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<11; j++)
        {
            possible_moves[i*11+j].push_back(0); //Poids
            for (int k=0; k<i; k++) possible_moves[i*11+j].push_back(0); //Entre 0 et 3 rotations possibles
            for (int k=0; k<5-j; k++) possible_moves[i*11+j].push_back(-1); //Plus ou moins à gauche
            for (int k=0; k<j-5; k++) possible_moves[i*11+j].push_back(1); //Plus ou moins à droite
        }
    }
    
    //calcul de la meilleur trajectoire
    for (int k=0; k<nb_pos_moves; k++)
    {
        //copie de tableau, pour chaque possibilité de placement de la pièce
        tableau* t = new tableau(tab_fantome);
        pieceActive_fantome._init_(t);

        //descente de la piece fantome dans le tableau fantome
        for (int i=1; i<(int)possible_moves[k].size()-1; i++)
        {
            switch(possible_moves[k][i])
            {
                case -1:
                    pieceActive_fantome.mouvement(t, "gauche");
                    break;
                case 0:
                    pieceActive_fantome.rotation(t);
                    break;
                case 1:
                    pieceActive_fantome.mouvement(t, "droite");
                    break;

                default:
                    std::cout << "Error in move research !!\n";
            }
        }
        while(pieceActive_fantome.getpieces()[0].getmobile() == true)
           pieceActive_fantome.mouvement(t, "bas");
        
        /* Debugage :
        for (int j=3; j<7; j++)
        {
            (*tab)(0,j).setidentifiant(0);
            (*tab)(1,j).setidentifiant(0);
            (*tab)(2,j).setidentifiant(0);
        }
        */

        //def du poids
        possible_moves[k][0] = calcul_poids(pieceActive_fantome, t, prev_nb_trous);
    }

    //recherche position de poids minimal
    int min = 10000, i_min = -1;
    for (int k=0; k<nb_pos_moves; k++)
    {
        if (possible_moves[k][0]<min)
        {
            min = possible_moves[k][0];
            i_min = k;
        }
    }
    ai_move = possible_moves[i_min];
}


/* une itération de jeu POUR AI, lancé automatiquement par le timer */
void jeu_ai::new_tick()
{
    iter_ai++;
    if(iter_ai >= (int)(numDiff/10) && !pauseActive && !finPartie)
    {
        if (i_move < (int) ai_move.size()-1)
            switch(ai_move[i_move])
            {
                case -1:
                    pieceActive.mouvement(tab, "gauche");
                    std::cout << "gauche ";
                    break;
                case 0:
                    pieceActive.rotation(tab);
                    std::cout << "rotation ";
                    break;
                case 1:
                    pieceActive.mouvement(tab, "droite");
                    std::cout << "droite ";
                    break;

                default:
                    std::cout << "Error in move research !!\n";
            }
        else descenteImmediate();
        i_move++;
        iter_ai = 0;
    }
    /* --> On enlève la descente automatique avec l'ia
    iter++;
    if(iter >= numDiff && !pauseActive && !finPartie)
    {
        pieceActive.mouvement(tab, "bas");  
        iter = 0;
    }
    */
    if(pieceActive.getpieces()[0].getmobile() == false){
            effacerLigne();
            tab->verif_fin_partie();
            finPartie = tab->getpartie_finie();
            if(!finPartie && !pauseActive)
            {
               pieceActive = buffer[0];
               pieceActive_fantome = new piece(&buffer[0]);
               tab_fantome = tab;
               buffer[0] = buffer[1];
               buffer[1] = piece(nombrePiece);nombrePiece++;
               int prev_nb_trous = nb_trous(tab, false);
               pieceActive._init_(tab);
               ai_move.clear();
               recherche_moves_ai(prev_nb_trous);
               i_move = 1;
               afficherBuffer();
            }
    }
    if(finPartie)
        pauseGame();

    afficherTableau(tab, pieceAffichees);
}
