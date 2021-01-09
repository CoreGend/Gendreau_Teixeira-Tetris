#include "piece.hpp"
#include "liste_piece.h"
#include "includers.h"

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
    switch (num_piece)
    {
        case 0:
            // Pièce 1 : "I", rien a vérifiéer
            break;
        
        case 1:
            // Pièce 2 : "O"
            for (int i=3; i>1; i--)
                if ((*tab)(parts[i].getligne(), parts[i].getcolonne()).getidentifiant() != 0)
                    esp_libre = 0;
            break;
        
        case 2:
            // Pièce 3 : "T"
            if ((*tab)(parts[3].getligne(), parts[3].getcolonne()).getidentifiant() != 0)
                esp_libre = 0;
            break;
        case 3:
            // Pièce 4 : "L"
            if ((*tab)(parts[0].getligne(), parts[0].getcolonne()).getidentifiant() != 0)
                esp_libre = 0;
            break;
        case 4:
            // Pièce 5 : "J"
            if ((*tab)(parts[3].getligne(), parts[3].getcolonne()).getidentifiant() != 0)
                esp_libre = 0;
            break;

        case 5:
            // Pièce 6 : "Z"
            for (int i=3; i>1; i--)
                if ((*tab)(parts[i].getligne(), parts[i].getcolonne()).getidentifiant() != 0)
                    esp_libre = 0;
            break;

        case 6:
            // Pièce 7 : "S"
            for (int i=0; i<3; i++)
                if ((*tab)(parts[i].getligne(), parts[i].getcolonne()).getidentifiant() != 0)
                    esp_libre = 0;
            break;
    }
    return esp_libre;
};

void piece::_intit_(tableau* tab)
{
    parts = liste_piece(num_piece, identifiant);
    bool init_standard_possible = init_piece_standard(tab);
    for (int i=0; i<nbDePiece; i++)
    {
        parts[i].setcolonne(parts[i].getcolonne() + (int)(tab->getlargeur()/2)-1);
        if (init_standard_possible)
        {
            parts[i].setligne(parts[i].getligne()+1);
            (*tab)(parts[i].getligne(), parts[i].getcolonne()) = parts[i];
            //(*tab)(parts[i].getligne() + 1, parts[i].getcolonne()) = parts[i];
        }
        else
            (*tab)(parts[i].getligne(), parts[i].getcolonne()) = parts[i];
    }
};

/* je voulais utiliser cette fonction pour vérifier si une part piece fait partie de la même pièce que celle que l'on considère
    pour éviter que les pièces voient leurs propres parties quand elles vérifient si elles peuvent bouger sur les côtés...
bool meme_part_piece(part_piece* pp, piece p)
{
    bool meme = false;
    for (int i=0; i<p.getndDePiece(); i++)
        if (pp == &(p.getpieces()[i])) meme = true;
    return meme;
}
*/

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
            {
                libre = 0;
            }
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
    else if (!strcmp(direction,"bas"))
    {
        if (place_libre(*tab, 1, 0))
            descend(tab);
        else
            stop();
    }
}

void piece::descend(tableau* tab)
{
    if (((num_piece==0 || num_piece==3 || num_piece==6) && rot < 2) || ((num_piece==1 || num_piece==2 || num_piece==4 || num_piece==5) && rot >= 2))
        for (int i=0; i<4; i++)
            (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne()+1, parts[i].getcolonne(), &parts[i]);
    else
        for (int i=3; i>=0; i--)
            (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne()+1, parts[i].getcolonne(), &parts[i]);
}

void piece::gauche(tableau* tab)
{
    if (rot >= 2)
    {
        for (int i=3; i>=0; i--)
        {
            (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne(), parts[i].getcolonne()-1, &parts[i]);
        }
    }
    else
    { 
        for (int i=0; i<4; i++)
        {
            (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne(), parts[i].getcolonne()-1, &parts[i]);
        }
    }
}

void piece::droite(tableau* tab)
{
    if (rot < 2)
    {
        // La liste prend les pièce de gauche à droite donc faut faire à l'envers
        for (int i=3; i>=0; i--)
        {
            (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne(), parts[i].getcolonne()+1, &parts[i]);
        }
    }
    else
    { //comme la gauche de base, mais je savais pas si on peut appeler deux fonctions les unes dans les autres...
        for (int i=0; i<4; i++)
        {
            (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne(), parts[i].getcolonne()+1, &parts[i]);
        }
    }
}


void piece::stop()
{ for (int i=0; i<nbDePiece; i++) parts[i].setmobile(false); }


void piece::rotation(tableau* tab)
{
    if (num_piece != 1)
    {
        int i_centre = 1;
        if (num_piece == 3 || num_piece == 6) i_centre = 2;
        int x_centre = parts[i_centre].getligne();
        int y_centre = parts[i_centre].getcolonne();
        for (int i=0; i<4; i++)
        {
            int x = parts[i].getligne();
            int y = parts[i].getcolonne();
            tab->changement_position(x, y, y-y_centre+x_centre, x_centre-x+y_centre, &parts[i]);
        }
        rot = (rot+1) %4;
    }
};
