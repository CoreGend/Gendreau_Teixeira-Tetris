#include "liste_piece.h"

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
