#include "jeu.h"
#include "bouton.h"
#include "afficheur.h"
#include "zoneJeu.h"
#include "tableau.hpp"
#include "piece.hpp"

jeu::jeu(QWidget *parent): QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);
}

void jeu::effacerLigne()
{
    int ligne_pleine = tab->reconnaissance_ligne();
    while (ligne_pleine != -1) //tant qu'il y a une ligne pleine
    {
        tab->effacement_ligne(ligne_pleine);
        qDebug() << "lignes effacees";
    }
}


void jeu::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Left)
        pieceActive.mouvement(tab, "gauche");
    else if (event->key() == Qt::Key_Right)
        pieceActive.mouvement(tab, "droite");
    else if (event->key() == Qt::Key_Down)
        pieceActive.mouvement(tab, "bas");

    QList<QGraphicsItem *> colliding_items = pieceAffichees[iactif]->collidingItems();
    for (int i=0; i<colliding_items.size(); ++i)
    {
        if(typeid(colliding_items[i]) == typeid(part_piece)){
            effacerLigne();
            afficherTableau();
            tab->verif_fin_partie();
            iteration();
        }
    }

}



piece jeu::genererPiece()
{
    piece new_piece;
   // qDebug() << "Nouvelle pièce !";
    new_piece._intit_(tab);
  //  qDebug() << "Mobile = " << new_piece.getpieces()[0].getmobile();
    return new_piece;
}
void jeu::afficherTableau()
{
    int hauteur = tab->gethauteur(); int largeur = tab->getlargeur();
    for(int i=0; i<hauteur; ++i)
    {
        for(int j=0; j<largeur; ++j)
        {
            if(tab->getliste()[(22-1-i)*10+j].getcouleur() != 0)
            {
                QBrush brush; brush.setColor(Qt::red); brush.setStyle(Qt::SolidPattern);
                pieceAffichees[(22-1-i)*10+j]->setBrush(brush);
          //      scene->addItem(pieceAffichees[i*10+j]);
            }
            else
            {
                QBrush brush; brush.setColor(Qt::white); brush.setStyle(Qt::SolidPattern);
                pieceAffichees[(22-1-i)*10+j]->setBrush(brush);
          //      scene->addItem(pieceAffichees[i*10+j]);
            }
        }
    }
}

void jeu::afficherFenetreJeu()
{
    QGraphicsTextItem* difficulteText = new QGraphicsTextItem("Difficulté");
    int posx = 50; int posy = 150;
    difficulteText->setPos(posx, posy);
    scene->addItem(difficulteText);

    afficheur* difficulte = new afficheur();
    posy=180;
    difficulte->setPos(posx, posy);
    scene->addItem(difficulte);

    bouton* lancer = new bouton(QString("Nouvelle partie"));
    posy=430;
    lancer->setPos(posx, posy);
    connect(lancer, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(lancer);

    bouton* quitter = new bouton(QString("Quitter"));
    posy = 500;
    quitter->setPos(posx, posy);
    connect(quitter, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitter);

    zoneJeu* zone = new zoneJeu;
    posx = 300; posy=80;
    zone->setPos(posx, posy);
    scene->addItem(zone);

    QGraphicsItem* scoreText = new QGraphicsTextItem("Score");
    posx=550; posy=200;
    scoreText->setPos(posx, posy);
    scene->addItem(scoreText);

    afficheur* score = new afficheur();
    posy=230;
    score->setPos(posx, posy);
    scene->addItem(score);

    QGraphicsTextItem* nbLigneText = new QGraphicsTextItem("Lignes completées");
    posy=300;
    nbLigneText->setPos(posx, posy);
    scene->addItem(nbLigneText);

    afficheur* nbLigne = new afficheur();
    posy=330;
    nbLigne->setPos(posx, posy);
    scene->addItem(nbLigne);

    for(int i=0; i<22; i++)
    {
        for(int j=0; j<10; j++)
        {
            pieceAffichees[i*10+j] = new QGraphicsRectItem;
            int posx = j*20+300; int posy = i*20+80;
            pieceAffichees[i*10+j]->setRect(posx, posy, 20,20);

            QBrush brush; brush.setColor(Qt::white); brush.setStyle(Qt::SolidPattern);
            pieceAffichees[i*10+j]->setBrush(brush);
            scene->addItem(pieceAffichees[i*10+j]);
        }
    }
}

void jeu::start()
{
    qDebug() << "Bouton appuyé !";
    tab = new tableau(22,10);

    iteration();
}

void jeu::iteration()
{
    pieceActive = genererPiece();
    iactif = pieceActive.getpieces()[0].getcolonne() + (21-pieceActive.getpieces()[0].getligne())*10;
    afficherTableau();
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(afficherTableau()));
    timer->start(200);
}
