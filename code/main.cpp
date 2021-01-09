#include "tableau.hpp"
#include "part_piece.hpp"
#include "piece.hpp"
#include "jeu.h"


void saut()
{
    std::cout << std::endl;
}

jeu* onJoue;

int main(int argc, char* argv[])
{
    srand(time(0));
    QApplication app(argc, argv);

    onJoue = new jeu();
    onJoue->show();

    return app.exec();

    /* Fait une partie toute seule de manière aléatoire. (mais assez stupidement quand même)
    tableau* tab = new tableau(6,6);
    tab->affichage();
    int nb_it = 0;
    srand(time(0));
    std::cout << "debut de partie : (partie finie = " << tab->getpartie_finie() << ").\n";

    while (!(tab->getpartie_finie()) && nb_it++ < 100)
    {
        piece new_piece;
        std::cout << "nouvelle piece !\n";
        new_piece._intit_(tab);
        std::cout << "mobile = " << new_piece.getpieces()[0].getmobile() << std::endl;
        tab->affichage();
        saut();
        while (new_piece.getpieces()[0].getmobile())
        {
            int type_mouvement = rand()%10;
            if (type_mouvement==0)
            {
                new_piece.mouvement(tab, "gauche");
            }
            else if (type_mouvement==1)
            {
                new_piece.mouvement(tab, "droite");
            }
            else
            {
                new_piece.mouvement(tab, "bas");
            }
            tab->affichage();
            time_t t1;
            time_t t2;
            time(&t1);
            time(&t2);
            while (t2-t1<1) time(&t2);
        }
        int ligne_pleine = tab->reconnaissance_ligne();
        while (ligne_pleine != -1) //tant qu'il y a une ligne pleine
        {
            tab->effacement_ligne(ligne_pleine);
            std::cout << "ligne effacee\n";
        }
        tab->verif_fin_partie();
        std::cout << "fin de la partie !!\n";
    }*/


    /* partie jouable pour 1 joueur. */
    /*
    tableau* tab = new tableau(6,6);
    tab->affichage();
    int nb_it = 0;
    srand(time(0));
    std::cout << "debut de partie : (partie finie = " << tab->getpartie_finie() << ").\n";

    while (!(tab->getpartie_finie()) && nb_it++ < 100)
    {
        piece new_piece;
        std::cout << "nouvelle piece !\n";
        new_piece._intit_(tab);
        std::cout << "mobile = " << new_piece.getpieces()[0].getmobile() << std::endl;
        tab->affichage();
        saut();
        while (new_piece.getpieces()[0].getmobile())
        {
            char type_mouvement;
            std::cin >> type_mouvement;
            if (type_mouvement=='q')
            {
                new_piece.mouvement(tab, "gauche");
            }
            else if (type_mouvement=='d')
            {
                new_piece.mouvement(tab, "droite");
            }
            else if (type_mouvement=='s')
            {
                new_piece.mouvement(tab, "bas");
            }
            tab->affichage();
        }
        int ligne_pleine = tab->reconnaissance_ligne();
        while (ligne_pleine != -1) //tant qu'il y a une ligne pleine
        {
            tab->effacement_ligne(ligne_pleine);
            std::cout << "ligne effacee\n";
        }
        tab->verif_fin_partie();
        std::cout << "fin de la partie !!\n";
    }
    return 0;
*/
}
