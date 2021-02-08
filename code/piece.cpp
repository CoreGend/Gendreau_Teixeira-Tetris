#include "piece.hpp"
#include "liste_piece.h"
#include "includers.h"
#include "globals.h"

int piece::getndDePiece() const
{ return nbDePiece; }

int piece::getnum_piece() const
{ return num_piece; }

int piece::getidentifiant() const
{ return identifiant; }

std::vector<part_piece> piece::getpieces() const
{ return parts; }

void piece::setidentifiant(int id)
{ identifiant = id; }


bool piece::init_piece_standard(tableau* tab)
{
    bool esp_libre = true;
    for (int i=0; i<nbDePiece; i++)
    {
        parts[i].setligne(parts[i].getligne()+1);
        parts[i].setcolonne(parts[i].getcolonne() + (int)(tab->getlargeur()/2)-1);
    }
    for (int i=0; i<nbDePiece; i++)
                if ((*tab)(parts[i].getligne(), parts[i].getcolonne()).getidentifiant() != 0)
                    esp_libre = false;
    return esp_libre;
}

void piece::_intit_(tableau* tab)
{
    parts = liste_piece(num_piece, identifiant);
    bool init_standard_possible = init_piece_standard(tab);
    if (!init_standard_possible) std::cout << "INITIALISATION SPECIALE !!!!" << std::endl;
    for (int i=0; i<nbDePiece; i++)
    {
        if (init_standard_possible)
        {
            (*tab)(parts[i].getligne(), parts[i].getcolonne()) = parts[i];
        }
        else
            (*tab)(parts[i].getligne()-1, parts[i].getcolonne()) = parts[i];
    }
};

void piece::placerPiece(tableau* tab, int hauteur, int largeur)
{
    int x, y;
    parts = liste_piece(num_piece, identifiant);
    for(int i=0; i<nbDePiece; i++)
    {
        x = largeur+parts[i].getcolonne(); y = hauteur+parts[i].getligne();
        parts[i].setcolonne(x);
        parts[i].setligne(y);
        (*tab)(y,x) = parts[i];
    }
}

bool piece::place_libre(tableau tab, int lig, int col)
{
    bool libre = 1;
    int i=0;
    while (i<nbDePiece && libre)
    {
        int identifiant_voisine = tab(parts[i].getligne()+lig, parts[i].getcolonne()+col).getidentifiant();

        if ( (identifiant_voisine != 0 && identifiant_voisine != parts[i].getidentifiant() )
        || parts[i].getligne()+lig >= tab.gethauteur()
        || parts[i].getcolonne()+col >= tab.getlargeur() || parts[i].getcolonne()+col < 0)
            { libre = 0; }
        i++;
    }
    return libre;
};

void piece::mouvement(tableau* tab, const char* direction)
{
    if (!strcmp(direction,"gauche") && place_libre(*tab, 0, -1))
        gauche(tab);
    else if (!strcmp(direction,"droite") && place_libre(*tab, 0, 1))
        droite(tab);
    else if (!strcmp(direction,"bas")){
        if (place_libre(*tab, 1, 0))
            descend(tab);
        else
            stop();
    }
}

void piece::descend(tableau* tab)
{
    int indice_tri[4];
    for(int i=0; i<4; i++) indice_tri[i] = i;
    int hauteur_i, hauteur_j, tmp_indice;
    for(int i=0; i<4; i++)
    {
        for(int j=i; j>=1; j--)
        {
            hauteur_i = parts[indice_tri[j-1]].getligne();
            hauteur_j = parts[indice_tri[j]].getligne();
            if(hauteur_j > hauteur_i){
                tmp_indice = indice_tri[j-1];
                indice_tri[j-1] = indice_tri[j];
                indice_tri[j] = tmp_indice;
            }
        }
    }
//    qDebug() << "[" << parts[indice_tri[0]].getligne() << parts[indice_tri[1]].getligne() << parts[indice_tri[2]].getligne() << parts[indice_tri[3]].getligne() << "]"
//             << "[" << indice_tri[0] << indice_tri[1] << indice_tri[2] << indice_tri[3] << "]";

    int ligne, colonne;
    for(int i=0; i<4; i++)
    {
        ligne = parts[indice_tri[i]].getligne();
        colonne = parts[indice_tri[i]].getcolonne();
        (*tab).changement_position(ligne, colonne, ligne+1, colonne, &parts[indice_tri[i]]);
     //   qDebug() << "Positions de piece : colonne, ligne | " << colonne << ", " << ligne;
    }
}

void piece::gauche(tableau* tab)
{
    int indice_tri[4];
    for(int i=0; i<4; i++) indice_tri[i] = i;
    int colonne_i, colonne_j, tmp_indice;
    for(int i=0; i<4; i++)
    {
        for(int j=i; j>=1; j--)
        {
            colonne_i = parts[indice_tri[j-1]].getcolonne();
            colonne_j = parts[indice_tri[j]].getcolonne();
            if(colonne_j < colonne_i){
                tmp_indice = indice_tri[j-1];
                indice_tri[j-1] = indice_tri[j];
                indice_tri[j] = tmp_indice;
            }
        }
    }
//    qDebug() << "[" << parts[indice_tri[0]].getcolonne() << parts[indice_tri[1]].getcolonne() << parts[indice_tri[2]].getcolonne() << parts[indice_tri[3]].getcolonne() << "]"
//             << "[" << indice_tri[0] << indice_tri[1] << indice_tri[2] << indice_tri[3] << "]";

    int ligne, colonne;
    for(int i=0; i<4; i++)
    {
        ligne = parts[indice_tri[i]].getligne();
        colonne = parts[indice_tri[i]].getcolonne();
        (*tab).changement_position(ligne, colonne, ligne, colonne-1, &parts[indice_tri[i]]);
    }
}

void piece::droite(tableau* tab)
{
    int indice_tri[4];
    for(int i=0; i<4; i++) indice_tri[i] = i;
    int colonne_i, colonne_j, tmp_indice;
    for(int i=0; i<4; i++)
    {
        for(int j=i; j>=1; j--)
        {
            colonne_i = parts[indice_tri[j-1]].getcolonne();
            colonne_j = parts[indice_tri[j]].getcolonne();
            if(colonne_j > colonne_i){
                tmp_indice = indice_tri[j-1];
                indice_tri[j-1] = indice_tri[j];
                indice_tri[j] = tmp_indice;
            }
        }
    }
//    qDebug() << "[" << parts[indice_tri[0]].getcolonne() << parts[indice_tri[1]].getcolonne() << parts[indice_tri[2]].getcolonne() << parts[indice_tri[3]].getcolonne() << "]"
//             << "[" << indice_tri[0] << indice_tri[1] << indice_tri[2] << indice_tri[3] << "]";

    int ligne, colonne;
    for(int i=0; i<4; i++)
    {
        ligne = parts[indice_tri[i]].getligne();
        colonne = parts[indice_tri[i]].getcolonne();
        (*tab).changement_position(ligne, colonne, ligne, colonne+1, &parts[indice_tri[i]]);
    }
}


void piece::stop()
{ for (int i=0; i<nbDePiece; i++) parts[i].setmobile(false); }


void piece::rotation(tableau* tab)
{
    /*  plus dur... il faut voir les objets en conflit et faire en sorte de les corriger
        nous travaillerons sur 5 listes : colonne et ligne avant et apres et indices */
    if(num_piece != 1)//la piece 1 ne tourne pas, carré
    {
        //la piece va tourner autour du centre
        int canRotate = true;;
        int largeur = tab->getlargeur();
        int hauteur = tab->gethauteur();
        int remplace;
        int i_centre = 1;
        if (num_piece == 3 || num_piece == 6) i_centre = 2;
        int x_centre = parts[i_centre].getcolonne();
        int y_centre = parts[i_centre].getligne();

        int x_cur, y_cur, dx, dy, j;
        int colonne_av[3], ligne_av[3], colonne_ap[3], ligne_ap[3], indices[3];
        for(int i=0; i<4; i++){
            if(i!=i_centre){
                if (i<i_centre) j=i;
                else j=i-1;
                x_cur = parts[i].getcolonne();
                y_cur = parts[i].getligne();
                dx = x_cur-x_centre; dy = y_cur-y_centre;
                indices[j]      = i;
                colonne_av[j]   = x_cur;
                ligne_av[j]     = y_cur;
                colonne_ap[j]   = x_centre-dy;
                ligne_ap[j]     = y_centre+dx;
                if(colonne_ap[j] < 0 || colonne_ap[j] >= largeur) canRotate = false;
                if(ligne_ap[j]>=hauteur) canRotate = false;
                remplace = tab->getliste()[colonne_ap[j]+ligne_ap[j]*largeur].getidentifiant();
                if(remplace!=identifiant && remplace!=0) canRotate = false;

  //              qDebug() << "[" << i << "]" << "(" << ligne_av[j] << "," << colonne_av[j] << ") -> (" << ligne_ap[j] << "," << colonne_ap[j] << ")";
            }
        }

        if(canRotate){
        /* puisqu'il y en a 3 et que ça tourne de 90°, il y en a forcément 1 qui ne remplacera pas un autre, on le cherche */
        bool remplace = false;
        int tmp;
        for(int i=0; i<3; i++)
        {
            remplace = false;
            for(int j=0; j<3; j++)
                if(j!=i && (colonne_ap[i]==colonne_av[j]) && (ligne_ap[i]==ligne_av[j]) )
                    remplace = true;

            /* on fait passer en 1er s'il remplace personne, il y en aura au moins un des 3 dans ce cas */
            if(!remplace)
            {
//                qDebug() << "(" << ligne_av[i] << "," << colonne_av[i] << ")" << "pousse en 1er !";
                for(int j=i-1; j>=0; j--)
                {
                    tmp = colonne_av[j+1]; colonne_av[j+1] = colonne_av[j]; colonne_av[j] = tmp;
                    tmp = colonne_ap[j+1]; colonne_ap[j+1] = colonne_ap[j]; colonne_ap[j] = tmp;
                    tmp = ligne_av[j+1]; ligne_av[j+1] = ligne_av[j]; ligne_av[j] = tmp;
                    tmp = ligne_ap[j+1]; ligne_ap[j+1] = ligne_ap[j]; ligne_ap[j] = tmp;
                    tmp = indices[j+1]; indices[j+1] = indices[j]; indices[j] = tmp;
                }
            }
        }
        /* à ce stade, on sait que le 1er remplace personne, il faut s'assurer qu'on est pas dans le cas de T et que le 2e remplace pas le 3, on échange sinon */
        if( (colonne_ap[1] == colonne_av[2]) && (ligne_ap[1] == ligne_av[2]) )
        {
            tmp = colonne_av[1]; colonne_av[1] = colonne_av[2]; colonne_av[2] = tmp;
            tmp = colonne_ap[1]; colonne_ap[1] = colonne_ap[2]; colonne_ap[2] = tmp;
            tmp = ligne_av[1]; ligne_av[1] = ligne_av[2]; ligne_av[2] = tmp;
            tmp = ligne_ap[1]; ligne_ap[1] = ligne_ap[2]; ligne_ap[2] = tmp;
            tmp = indices[1]; indices[1] = indices[2]; indices[2] = tmp;
        }

        /* maintenant on peut faire tourner la piece */
        for(int i=0; i<3; i++)
        {
//            qDebug() << "(" << ligne_av[i] << "," << colonne_av[i] << ") -> (" << ligne_ap[i] << "," << colonne_ap[i] << ")";
            tab->changement_position(ligne_av[i], colonne_av[i], ligne_ap[i], colonne_ap[i], &parts[indices[i]]);
        }

        rot = (rot+1) %4;
        }
        else{ qDebug() << "impossible de tourner"; }
    }
}
