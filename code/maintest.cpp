#include "tableau.hpp"
#include "part_piece.hpp"
#include "piece.hpp"

void saut()
{
    std::cout << std::endl;
}

int main ()
{
    tableau* tab = new tableau(6,6);
    tab->affichage();
    piece new_piece;
    new_piece._intit_(tab);
    tab->affichage();
    std::cout << std::endl;
    new_piece.mouvement(tab, "bas");
    tab->affichage();
    saut();
    new_piece.mouvement(tab, "gauche");
    tab->affichage();
    saut();
    new_piece.mouvement(tab, "droite");
    tab->affichage();
    saut();
    new_piece.mouvement(tab, "droite");
    tab->affichage();
    saut();
    new_piece.mouvement(tab, "droite");
    tab->affichage();
    saut();
    new_piece.mouvement(tab, "droite");
    tab->affichage();
    saut();
    new_piece.mouvement(tab, "droite");
    tab->affichage();
    saut();
    new_piece.mouvement(tab, "bas");
    tab->affichage();

/* TEST 1
    part_piece piece1(1,2,1);
    part_piece piece2(2,1,1);
    part_piece piece3(1,0,1);
    part_piece piece4(1,1,2);
    tab(1,2) = piece1;
    tab(1,0) = piece2;
    tab(2,1) = piece2;
    tab(1,1) = piece4;
    tab.affichage();

    

    tab.verif_fin_partie();
    int i_ligne_pleine = tab.reconnaissance_ligne();
    std::cout << "partie finie : " << ( tab.getpartie_finie() ? "oui": "non" ) << std::endl;
    std::cout << "ligne pleine en " << i_ligne_pleine << "e position\n";
    tab.affichage();

    tab.changement_position(1,1,0,0);
    tab.affichage();

    tab.verif_fin_partie();
    std::cout << "partie finie : " << ( tab.getpartie_finie() ? "oui": "non" ) << std::endl;

    tab.effacement_ligne(1);
    tab.affichage();
*/

    //tab.effacement_ligne(i_ligne_pleine);
    //tab.affichage();

    //tab.getliste()[tab.pos(1,1)]->getcolonne() = 2;

    //delete tab;
    return 0;
}
