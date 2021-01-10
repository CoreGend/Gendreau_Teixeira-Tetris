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
    /* PARTIE DROITE */
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

    /* PARTIE CENTRALE */
    //peut être supprimé
    QBrush brush; brush.setColor(Qt::white); brush.setStyle(Qt::NoBrush);
    QPen pen; pen.setWidthF(0.1);
    for(int i=0; i<22; i++)
    {
        for(int j=0; j<10; j++)
        {
            pieceAffichees[i*10+j] = new QGraphicsRectItem;
            posx = j*20+300; posy = i*20+80;
            pieceAffichees[i*10+j]->setRect(posx, posy, 20,20);

            pieceAffichees[i*10+j]->setBrush(brush);
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


    /* PARTIE GAUCHE */
    QGraphicsItem* piecesText = new QGraphicsTextItem("Prochaines pièces");
    posx=550; posy=100;
    piecesText->setPos(posx, posy);
    scene->addItem(piecesText);


    for(int x=0; x<9; x++)
        for(int y=0; y<2; y++)
        {
            pieceBuffer[y*9+x] = new QGraphicsRectItem;
            posx = x*20+550; posy = y*20+130;
            pieceBuffer[y*9+x]->setRect(posx, posy, 20,20);

            pieceBuffer[y*9+x]->setBrush(brush);
            pieceBuffer[y*9+x]->setPen(Qt::NoPen);
            scene->addItem(pieceBuffer[y*9+x]);
        }

    posx = 550;

    QGraphicsItem* scoreText = new QGraphicsTextItem("Score");
    posy=200;
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
void jeu::afficherTableau(tableau* loc_tab, QGraphicsRectItem** listePieces)
{
    int hauteur = loc_tab->gethauteur(); int largeur = loc_tab->getlargeur();
    QBrush brush; brush.setStyle(Qt::SolidPattern);
    for(int i=0; i<hauteur; ++i)
    {
        for(int j=0; j<largeur; ++j)
        {
            switch( (loc_tab->getliste()[i*largeur+j]).getcouleur())
            {
            case 0:
                brush.setColor(Qt::cyan);
                break;
            case 1:
            {
                QColor color;
                color.setRgb(239,221,0,255);
                brush.setColor(color);
                break;
            }
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

            listePieces[i*largeur+j]->setBrush(brush);
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

void jeu::afficherBuffer()
{
    // buffer[0] et buffer[1] sont des pieces, on veut les afficher
    buff->reset();

    buffer[0].placerPiece(buff, 0,1);
    buffer[1].placerPiece(buff, 0,6);

    afficherTableau(buff, pieceBuffer);
}

/* lancement du jeu en créant le tableau de jeu, initialisant tout et créant le timer */
void jeu::start(){
    tab = new tableau(22,10);
    buff = new tableau(2,9);
    removeText();

    pieceActive = genererPiece();
    buffer[0] = piece();
    buffer[1] = piece();

    diff = 1; newDiff();

    afficherTableau(tab, pieceAffichees);
    afficherBuffer();

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
            {
               pieceActive = buffer[0];
               buffer[0] = buffer[1];
               buffer[1] = piece();
               pieceActive._intit_(tab);
               afficherBuffer();
            }
    }
    if(finPartie)
        pauseGame();

    afficherTableau(tab, pieceAffichees);
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
