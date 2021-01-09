#include "jeu.h"
#include "bouton.h"
#include "zoneJeu.h"
#include "tableau.hpp"
#include "piece.hpp"

/* constructeur */
jeu::jeu(QWidget *parent): QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);

    afficherFenetreJeu();
}

/* crée la fenêtre de jeu avec les différents éléments
   dedans (boutons, zones d'affichage de score...) */
void jeu::afficherFenetreJeu()
{
    QGraphicsTextItem* difficulteText = new QGraphicsTextItem("Difficulté");
    int posx = 50; int posy = 150;
    difficulteText->setPos(posx, posy);
    scene->addItem(difficulteText);

    difficulte = new afficheur(1);
    posy=180;
    difficulte->setPos(posx, posy);
    scene->addItem(difficulte);

    bouton* lancer = new bouton(QString("Nouvelle partie"));
    posy=360;
    lancer->setPos(posx, posy);
    connect(lancer, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(lancer);

    bouton* pause = new bouton(QString("Pause"));
    posy=430;
    pause->setPos(posx, posy);
    connect(pause, SIGNAL(clicked()), this, SLOT(pauseGame()));
    scene->addItem(pause);

    bouton* quitter = new bouton(QString("Quitter"));
    posy = 500;
    quitter->setPos(posx, posy);
    connect(quitter, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitter);

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
            QPen pen; pen.setWidthF(0.1);
            pieceAffichees[i*10+j]->setPen(pen);
            scene->addItem(pieceAffichees[i*10+j]);
        }
    }

    inGameTextZone = new QGraphicsRectItem;
    inGameTextZone->setRect(300,250, 200,100);
    inGameTextZone->setPen(Qt::NoPen);

    inGameText = new QGraphicsTextItem(inGameTextZone);
    posx = 300+inGameTextZone->rect().width()/2 - inGameText->boundingRect().width()/2;
    posy = 200+inGameTextZone->rect().height()/2 - inGameText->boundingRect().height()/2;
    inGameText->setPos(posx, posy);

    QFont font;
    font.setWeight(QFont::Bold); font.setPointSize(font.pointSize()+16);
    inGameText->setFont(font);

    scene->addItem(inGameTextZone);
}

/* génération d'une pièce */
piece jeu::genererPiece()
{
    piece new_piece;
    new_piece._intit_(tab);
    return new_piece;
}

/*  fonction appelée lorsqu'une pièce tombe,
        vérifie s'il y a des lignes complètes
        les efface en comptant le nombre de lignes effacées
        change le score en fonction du nombre de lignes effacées */
void jeu::effacerLigne()
{
    int ligne_pleine = tab->reconnaissance_ligne();
    int nbLigneEff = 0;

    while (ligne_pleine != -1) //tant qu'il y a une ligne pleine
    {
        tab->effacement_ligne(ligne_pleine);
        ligne_pleine = tab->reconnaissance_ligne();
        nbLigneEff++;
    }

    if      (nbLigneEff == 1) scoreValue += diff*40;
    else if (nbLigneEff == 2) scoreValue += diff*100;
    else if (nbLigneEff == 3) scoreValue += diff*300;
    else if (nbLigneEff == 4) scoreValue += diff*1200;
    score->changerValeur(scoreValue);

    nbLigneEffacees += nbLigneEff;
    nbLigne->changerValeur(nbLigneEffacees);

    ( (1+nbLigneEffacees/10)< 13) ? (diff = 1+nbLigneEffacees/10 ) : diff = 13;
    difficulte->changerValeur(diff);
    newDiff();
}

/*  affiche le tableau graphique en se basant sur le tableau de jeu */
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
            case 2:
                brush.setColor(Qt::darkMagenta);
                break;
            case 3:
            {
                QColor color;
                color.setRgb(255,119,0,255);
                brush.setColor(color);
                break;
            }
            case 4:
                brush.setColor(Qt::blue);
                break;
            case 5:
                brush.setColor(Qt::red);
                break;
            case 6:
                brush.setColor(Qt::green);
                break;
            default:
                brush.setColor(Qt::white);
            }

            pieceAffichees[i*10+j]->setBrush(brush);
        }
    }
}

/*  fonction qui survient lorsqu'une touche est appuyée */
void jeu::keyPressEvent(QKeyEvent* event)
{
    if(!pauseActive && !finPartie){
    if(event->key() == Qt::Key_Left)
        pieceActive.mouvement(tab, "gauche");
    else if (event->key() == Qt::Key_Right)
        pieceActive.mouvement(tab, "droite");
    else if (event->key() == Qt::Key_Up)
        pieceActive.rotation(tab);
    else if (event->key() == Qt::Key_Down){
        pieceActive.mouvement(tab, "bas");
        scoreValue+=1;
        score->changerValeur(scoreValue);
        qDebug() << "descente";
    }
    }
}

/*  modifie la difficulcuté de jeu cf. définition des variables dans le .hpp */
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

/* lancement du jeu en créant le tableau de jeu, initialisant tout et créant le timer */
void jeu::start(){
    tab = new tableau(22,10);
    removeText();

    pieceActive = genererPiece();
    diff = 1; newDiff();

    afficherTableau();

    if(enJeu == false)
    {
        QTimer* timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(new_tick()));
        timer->start(16);
        enJeu = true;
    }
    else
    {
        scoreValue = 0; score->changerValeur(scoreValue);
        nbLigneEffacees = 0; nbLigne->changerValeur(nbLigneEffacees);
        difficulte->changerValeur(diff);
        pauseActive = false;
        finPartie = false;
    }
}

/* une itération de jeu, lancé automatiquement par le timer */
void jeu::new_tick()
{
    iter++;
    if(iter >= numDiff && !pauseActive && !finPartie)
    {
        pieceActive.mouvement(tab, "bas");
        iter = 0;
    }
    if(pieceActive.getpieces()[0].getmobile() == false){
            effacerLigne();
            tab->verif_fin_partie();
            finPartie = tab->getpartie_finie();
            if(!finPartie && !pauseActive)
               pieceActive = genererPiece();
    }
    if(finPartie)
        pauseGame();

    afficherTableau();
}

void jeu::pauseGame()
{
    if (enJeu && !finPartie)
        pauseActive = !pauseActive;

    if (pauseActive)
        insertText(QString("Pause"));
    if (finPartie)
        insertText(QString("Partie Finie"));
    if(!pauseActive && !finPartie)
        removeText();
}

void jeu::insertText(QString text)
{
    inGameText->setPlainText(text);
    int posx = 300+inGameTextZone->rect().width()/2 - inGameText->boundingRect().width()/2;
    int posy = 250+inGameTextZone->rect().height()/2 - inGameText->boundingRect().height()/2;
    inGameText->setPos(posx, posy);

    QPen pen; pen.setStyle(Qt::SolidLine); pen.setWidth(4);
    inGameTextZone->setPen(pen);
}

void jeu::removeText()
{
    inGameText->setPlainText("");
    int posx = 350+inGameTextZone->rect().width()/2 - inGameText->boundingRect().width()/2;
    int posy = 275+inGameTextZone->rect().height()/2 - inGameText->boundingRect().height()/2;
    inGameText->setPos(posx, posy);
    inGameTextZone->setPen(Qt::NoPen);
}
