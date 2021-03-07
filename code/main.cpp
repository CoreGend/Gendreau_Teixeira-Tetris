#include "tableau.hpp"
#include "part_piece.hpp"
#include "piece.hpp"
#include "jeu.h"
#include "jeu_ai.h"
#include "globals.h"


void saut()
{
    std::cout << std::endl;
}

jeu* onJoue;
jeu_ai* AIjoue;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    seed = rand();

    QApplication app(argc, argv);

/* JEU TETRIS 1 JOUEUR
    onJoue = new jeu();
    onJoue->show();
*/
/* JEU TETRIS 1 AI*/
    AIjoue = new jeu_ai();
    AIjoue->show();

    return app.exec();
}
