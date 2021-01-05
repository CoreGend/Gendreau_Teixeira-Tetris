#include "piece.hpp"
#include "includers.h"

int piece::getndDePiece() const {return nbDePiece;};
int piece::getnum_piece() const {return num_piece;};
int piece::getidentifiant() const {return identifiant;};
std::vector<part_piece> piece::getpieces() const {return parts;};

void piece::setidentifiant(int id) {identifiant = id;};
void piece::setpieces(std::vector<part_piece> blocs) {parts = blocs;};

std::vector<part_piece> liste_piece(int num, int identifiant)
{
    /* fonctionne pour des pièces constituées de 4 parties de pièces seuelemnt pour le moment. */

    part_piece* p1 = (part_piece*) malloc(sizeof(part_piece));
    part_piece* p2 = (part_piece*) malloc(sizeof(part_piece));
    part_piece* p3 = (part_piece*) malloc(sizeof(part_piece));
    part_piece* p4 = (part_piece*) malloc(sizeof(part_piece));

    p1->setidentifiant(identifiant);
    p2->setidentifiant(identifiant);
    p3->setidentifiant(identifiant);
    p4->setidentifiant(identifiant);

    p1->setcouleur(num);
    p2->setcouleur(num);
    p3->setcouleur(num);
    p4->setcouleur(num);

    p1->setmobile(true);
    p2->setmobile(true);
    p3->setmobile(true);
    p4->setmobile(true);

    std::vector<part_piece> blocs;

    switch (num)
    {
        case 0:
            // Pièce 1 : "I"
            p1->setcoordonnees(0,-1);
            p2->setcoordonnees(0,0);
            p3->setcoordonnees(0,1);
            p4->setcoordonnees(0,2);
            blocs = {*p1, *p2, *p3, *p4};
            break;
        
        case 1:
            // Pièce 2 : "O"
            p1->setcoordonnees(0,0);
            p2->setcoordonnees(0,1);
            p3->setcoordonnees(1,0);
            p4->setcoordonnees(1,1);
            blocs = {*p1, *p2, *p3, *p4};
            break;
        
        case 2:
            // Pièce 3 : "L"
            p1->setcoordonnees(1,-1);
            p2->setcoordonnees(0,-1);
            p3->setcoordonnees(0,0);
            p4->setcoordonnees(0,1);
            blocs = {*p1, *p2, *p3, *p4};
            break;

        case 3:
            // Pièce 4 : "J"
            p1->setcoordonnees(0,-1);
            p2->setcoordonnees(0,0);
            p3->setcoordonnees(0,1);
            p4->setcoordonnees(1,1);
            blocs = {*p1, *p2, *p3, *p4};
            break;

        case 4:
            // Pièce 5 : "Z"
            p1->setcoordonnees(0,-1);
            p2->setcoordonnees(0,0);
            p3->setcoordonnees(1,0);
            p4->setcoordonnees(1,1);
            blocs = {*p1, *p2, *p3, *p4};
            break;

        case 5:
            // Pièce 6 : "S"
            p1->setcoordonnees(1,-1);
            p2->setcoordonnees(1,0);
            p3->setcoordonnees(0,0);
            p4->setcoordonnees(0,1);
            blocs = {*p1, *p2, *p3, *p4};
            break;
        default:
            qDebug() << "Numero de piece non connu\n";
            blocs = {-1,-1,-1,-1};
    }
    return blocs;
};

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
            // Pièce 3 : "L"
            if ((*tab)(parts[0].getligne(), parts[0].getcolonne()).getidentifiant() != 0)
                esp_libre = 0;
            break;

        case 3:
            // Pièce 4 : "J"
            if ((*tab)(parts[3].getligne(), parts[3].getcolonne()).getidentifiant() != 0)
                esp_libre = 0;
            break;

        case 4:
            // Pièce 5 : "Z"
            for (int i=3; i>1; i--)
                if ((*tab)(parts[i].getligne(), parts[i].getcolonne()).getidentifiant() != 0)
                    esp_libre = 0;
            break;

        case 5:
            // Pièce 6 : "S"
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
    for (int i=0; i<nbDePiece; i++)
    {
        parts[i].setcolonne(parts[i].getcolonne() + (int)(tab->getlargeur()/2));
        if (init_piece_standard(tab))
            parts[i].setligne(parts[i].getligne()+1);
            //(*tab)(parts[i].getligne() + 1, parts[i].getcolonne()) = parts[i];
        else
        {
 //           qDebug() << "Special init\n";
            (*tab)(parts[i].getligne(), parts[i].getcolonne()) = parts[i];
        }
        //std::cout << "piece placee en " << parts[i].getligne()<< "," << parts[i].getcolonne() << std::endl;
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
                qDebug() << tab(parts[i].getligne()+lig, parts[i].getcolonne()+col).getidentifiant();
                libre = 0;
            }
        i++;
    }
    return libre;
};

void piece::mouvement(tableau* tab, const char* direction)
{
    if (!strcmp(direction,"gauche"))
    {
        if (place_libre(*tab, 0, -1))
        {
  //          qDebug() << "deplacement de piece vers la gauche :\n";
            gauche(tab);
        }
        else
        {
            qDebug() << "la piece ne peut pas bouger...\n";
        }
    }
    else if (!strcmp(direction,"droite"))
    {
        if (place_libre(*tab, 0, 1))
        {
 //           qDebug() << "deplacement de piece vers la droite :\n";
            droite(tab);
        }
        else
        {
            qDebug() << "la piece ne peut pas bouger...\n";
        }
    }
    else if (!strcmp(direction,"bas"))
    {
        if (place_libre(*tab, 1, 0))
        {
  //          qDebug() << "deplacement de piece vers le bas :\n";
            descend(tab);
        }
        else
        {
            qDebug() << "la piece se pose\n";
            stop();
        }
    }
};

void piece::descend(tableau* tab)
{
    switch (num_piece)
    {
        case 0://I : pas besoin de s'embeter tout peut descendre dans l'ordre
            for (int i=0; i<4; i++)
            {
                (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne()+1, parts[i].getcolonne(), &parts[i]);
            }
            break;
        case 1://O : il faut faire descendre d'abord le bas ie partpiece d'indice 2 et 3 dans la liste
            for (int i=3; i>=0; i--)
            {
                (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne()+1, parts[i].getcolonne(), &parts[i]);
            }
            break;
        case 2://L : ok c'est déjç dans le bon ordre
            for (int i=0; i<4; i++)
            {
                (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne()+1, parts[i].getcolonne(),&parts[i]);
            }
            break;
        case 3://J : la dernière pièce de la liste doit descendre en 1er
            for (int i=3; i>=0; i--)
            {
                (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne()+1, parts[i].getcolonne(), &parts[i]);
            }
            break;
        case 5://S : ok
            for (int i=0; i<4; i++)
            {
                (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne()+1, parts[i].getcolonne(), &parts[i]);
            }
            break;
        case 4://Z : à l'envers
            for (int i=3; i>=0; i--)
            {
                (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne()+1, parts[i].getcolonne(), &parts[i]);
            }
            break;
    }
}

void piece::gauche(tableau* tab)
{
    // La liste prend les pièce de gauche à droite donc pas de problèmes
    for (int i=0; i<4; i++)
    {
        (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne(), parts[i].getcolonne()-1, &parts[i]);
    }
}

void piece::droite(tableau* tab)
{
    // La liste prend les pièce de gauche à droite donc faut faire à l'envers
    for (int i=3; i>=0; i--)
    {
        (*tab).changement_position(parts[i].getligne(), parts[i].getcolonne(), parts[i].getligne(), parts[i].getcolonne()+1, &parts[i]);
    }
}


void piece::stop()
{
    for (int i=0; i<nbDePiece; i++) parts[i].setmobile(false);
}


void piece::rotation()
{};
