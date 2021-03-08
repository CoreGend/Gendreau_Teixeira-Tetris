# Projet IN204 : Corentin GENDREAU / Quentin TEIXEIRA
# Tétris

## Installation du support du code

Pour compiler et exécuter notre code, on utilise Qt Creator. Il faut donc l'installer pour pouvoir jouer à notre tétris.
Après l'avoir installé, il faut ouvrir le dossier code et exécuter code.exe.

## Présentation du projet

Le dossier 'réflexion initiale' donne des informations sur les idées principales que l'on a adoptées dès le début du projet.

Le code du projet est stocké dans le dossier 'code'.

### code du Tetris

Différentes choses ont été codées sur Qt:

#### Un tétris fonctionnel pour un unique joueur
L'interface propose plusieurs choses intéressantes en plus du jeu en lui-même. On voit évidemment le plateau de jeu, les pièces posées et celle qui est en train de tomber, mais aussi notre score actuel, les deux pièces suivantes, le nombre de lignes effacées, la difficultée du jeu (qui augmente naturellement au fur et à mesure du jeu tant que l'on ne perd pas). On peut également mettre le jeu sur pause à tout moment, relancer une nouvelle partie ou quitter le jeu grâce aux boutons en bas à gauche de l'interface.

Les classes et méthodes sont assez intuitives et compréhensible avec leur nom.
Juste un petit détail sur le fonctionnement global du jeu: la grille de jeu (taleau.cpp) contient des 'part_pièce' (part_pièce.cpp : parties de pièces), et de même, chaque 'pièce' (pièce.cpp) contient des 'part_pièces'. Ainsi, on manipule une 'pièce' tant qu'elle n'est pas tombée (elle gère ses propores 'part_pièces'), puis la 'pièce' est laissée de côté. C'est par le tableau que seront ensuite manipulées les 'part_pièces' (par exemple lors d'effacement de ligne pour le déplacement...)


#### Un IA qui joue seul
Pour faire tourner l'IA, il faut commenter/décommenter ce qu'il faut dans le fichier main.cpp (2 lignes).
L'IA fonctionne ainsi:
    Pour chaque nouvelle pièce, on va regarder tous les mouvements possibles (détaillé plus loin). Pour cela, pour chaque série de mouvements (rotation, gauche ou droite répété plusieurs fois), on crée une copie du tableau en cours et de la pièce pour faire descendre la pièce 'fantôme' dans ce tableau 'fantôme'. Chaque série de mouvement se voit alors attribué un poids variant selon que la position d'arrêt est bonne ou mauvaise. Trois choses ont été considérées pour ce poids pour le moment: La hauteur d'arrivée de la pièce (compte peu, mais est quand même important), le nombre de trous entre les pièces créés par l'arrivée de la nouvelle pièce (compte pas mal), et le nombre de ligne effacées (compte beaucoup). Il suffit ensuite de prendre la série de mouvement au poids le plus faible pour avoir la position d'arrivée optimale.

Pistes d'amélioration de l'IA:
    - On pourrait prendre en compte plus de séries de mouvements pour pouvoir incruster des pièces entre elles, car dans notre version les pièces ne peuvent que tomber en lignes droite (elles ne peuvent pas se décaller vers la droite ou le gauche au ernier moment par exemple...). Cela prendrait beaucoup plus de temps de calcul cependant, ce serait à prendre en compte das la faisabilité de cette initiative.
    - On pourrait utiliser la fonctionnalité 'tenir la pièce' pour calculer les poids liés aux série de mouvements de la pièce suivante et voir s'il y a mieux à faire avec celle ci.

Problème principal rencontré:
    Le fait de créer des tableaux et des pièces fantômes en masse ne plaît pas beaucoup à l'espace mémoire il nous semble. Cela a pour conséquence des crashs réguliers de l'application... D'ailleurs il semblerait qu'exécuter le code IA en mode débuggage augmente significativement le temps de jeu sans crash. C'est un mystère...

#### Un tetris sur réseau pour du multijoueur ?
Pour pouvoir jouer en réseau, l'option de l'architecture client-serveur a été choisie. Celle-ci permet de bien supporter la scalabilité (ainsi nous pourrons faire passer le jeu de 1 contre 1 à plusieurs joueurs).
Nous avons donc utilisé les outils offerts par Qt pour créer cette architecture.
Le serveur fonctionne de la sorte : les joueurs envoient des paquets contenant leur score et le serveur les renvoie à tout le monde.
L'ouverture d'un serveur fonctionne de la sorte: si le joueur appuie sur le bouton "ouvrir serveur", un serveur Qt est ouvert. Les autres joueurs peuvent le rejoindre via le réseau LAN ou internet (le joueur doit aussi rejoindre le réseau) en cliquant sur "rejoindre le serveur" et en entrant l'IP de l'hôte

Initialement nous voulions que le score de l'adversaire soit affiché en temps réel, mais en fait le fonctionnement du serveur est incorrect. Il devrait renvoyer à l'adversaire le score et pas au joueur qui l'a envoyé... Faute de quoi le score adverse affiché varie incessamment entre... Le score adverse et le score du joueur.
C'est là une piste d'amélioration.
Nous pouvons aussi essayer d'implémenter des scores pour plus que 2 joueurs, alors une identification entre les joueurs serait nécessaire. Cette même identification pourrait servir à corriger le problème soulevé.
L'affichage du plateau adverse peut se faire mais couterait plus cher (fenêtre à modifier notamment).
Nous pourrions aussi faire un tableau des meilleurs score de la session si les joueurs restent connectés pendant plusieurs parties.
Plus généralement, une fois le multijoueur implémenté une floppée d'améliorations sont envisageables.