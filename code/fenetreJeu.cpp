#include "fenetreJeu.h"

fenetreJeu::fenetreJeu(QWidget* parent): QGraphicsView(parent)
{
    scene = new QGraphicsScene;
    vue = new QGraphicsView;

    bouton* test = new bouton("test");
    quitter = new bouton("Quitter");
    int posx = 10; int posy = 10;
    quitter->setPos(posx, posy);

//    scoreText->setPlainText("Score");
//    difficulteText->setPlainText("Difficulte");
//    nbLigneText->setPlainText("Nombre de lignes complétées");

    scene->setSceneRect(0,0,800,600);

    vue = new QGraphicsView(scene);

    vue->setSceneRect(0,0,800,600);
    scene->addItem(quitter);

    vue->show();
}
