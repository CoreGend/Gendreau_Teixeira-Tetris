#include "jeu.h"
#include "bouton.h"
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
    int nbLigneEff = 0;
//    qDebug() << "ligne reconnue : " << ligne_pleine;
    while (ligne_pleine != -1) //tant qu'il y a une ligne pleine
    {
        tab->effacement_ligne(ligne_pleine);
        ligne_pleine = tab->reconnaissance_ligne();
        nbLigneEff++;
        qDebug() << "lignes effacees";
    }
    if(nbLigneEff == 1) scoreValue += 40;
    else if (nbLigneEff == 2) scoreValue+=100;
    else if(nbLigneEff == 3) scoreValue += 300;
    else if(nbLigneEff == 4) scoreValue += 1200;
    score->changerValeur(scoreValue);

    nbLigneEffacees += nbLigneEff;
    nbLigne->changerValeur(nbLigneEffacees);

    (nbLigneEffacees/10 + 1< 13) ? (diff = nbLigneEffacees/10 + 1 ) : diff = 13;
    difficulte->changerValeur(diff);
    newDiff();
}


void jeu::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Left)
        pieceActive.mouvement(tab, "gauche");
    else if (event->key() == Qt::Key_Right)
        pieceActive.mouvement(tab, "droite");
    else if (event->key() == Qt::Key_Down){
        pieceActive.mouvement(tab, "bas");
        scoreValue+=1;
        score->changerValeur(scoreValue);
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
            QBrush brush; brush.setStyle(Qt::SolidPattern);
            switch( (tab->getliste()[i*10+j]).getcouleur())
            {
            case 0:
                brush.setColor(Qt::cyan);
                break;
            case 1:
                brush.setColor(Qt::yellow);
                break;
       //     case 2:
       //         brush.setColor(Qt::darkMagenta);
       //         break;
            case 2:
            {
                QColor color;
                color.setRgb(255,119,0,255);
                brush.setColor(color);
                break;
            }
            case 3:
                brush.setColor(Qt::blue);
                break;
            case 4:
                brush.setColor(Qt::red);
                break;
            case 5:
                brush.setColor(Qt::green);
                break;
            default:
                brush.setColor(Qt::white);
            }

            pieceAffichees[i*10+j]->setBrush(brush);
        }
    }
}

void jeu::afficherFenetreJeu()
{
    QGraphicsTextItem* difficulteText = new QGraphicsTextItem("Difficulté");
    int posx = 50; int posy = 150;
    difficulteText->setPos(posx, posy);
    scene->addItem(difficulteText);

    difficulte = new afficheur();
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

    score = new afficheur();
    posy=230;
    score->setPos(posx, posy);
    scene->addItem(score);

    QGraphicsTextItem* nbLigneText = new QGraphicsTextItem("Lignes completées");
    posy=300;
    nbLigneText->setPos(posx, posy);
    scene->addItem(nbLigneText);

    nbLigne = new afficheur();
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

            QBrush brush; brush.setColor(Qt::white); brush.setStyle(Qt::NoBrush);
            pieceAffichees[i*10+j]->setBrush(brush);
          //  pieceAffichees[i*10+j]->setPen(Qt::NoPen);
            scene->addItem(pieceAffichees[i*10+j]);
        }
    }
}

void jeu::newDiff()
{
    switch(diff)
    {
    case 1:
        numDiff = 60;
        break;
    case 2:
        numDiff = 48;
        break;
    case 3:
        numDiff = 37;
        break;
    case 4:
        numDiff = 28;
        break;
    case 5:
        numDiff = 21;
        break;
    case 6:
        numDiff = 16;
        break;
    case 7:
        numDiff = 11;
        break;
    case 8:
        numDiff = 8;
        break;
    case 9:
        numDiff = 6;
        break;
    case 10:
        numDiff = 4;
        break;
    case 11:
        numDiff = 3;
        break;
    case 12:
        numDiff = 2;
        break;
    case 13:
        numDiff = 1;
        break;
    }
}
void jeu::new_tick()
{
    iter++;
    if(iter >= numDiff)
    {
        pieceActive.mouvement(tab, "bas");
        iter = 0;
    }
    if(pieceActive.getpieces()[0].getmobile() == false){
            effacerLigne();
            tab->verif_fin_partie();
            pieceActive = genererPiece();
    }
    afficherTableau();
    qDebug() << "Hey!";
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
    diff = 1; newDiff();
    afficherTableau();
    if(enJeu == 0)
    {
        QTimer* timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(new_tick()));
        timer->start(16);
        enJeu++;
    }
}
