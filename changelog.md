23/01/2021


22/01/2021
- ajout du pseudo aléatoire avec la graine
- modification de l'usage de l'identifiant (qui correspond maintenant à la réponse à 
la question "c'est la combientième pièce créée ?")
- pseudo aléatoire : numéro de pièce = graine/identifiant mod 7

12/01/2021
principaux :
- ajout de la descente immédiate

11/01/2021
principaux :
- correction de l'erreur permettant aux pièces de traverser les murs et remplacer des pièces

10/10/2021 (Corentin)
principaux:
- correction des mouvements des pièces (rotation et déplacements)
- ajout du buffer de pièces

09/01/2021 (Corentin)
principaux :
- ajout d'une fonctionnalité de pause
- ajout d'une fonctionnalité de recommancement de partie
- ajout de la fin du jeu
- ajout de la prise en compte de la rotation
correction de bug :
- le jeu se termine bien maintenant quand on ne peut plus poser de pièce
- la difficulté est maintenant initialisée à 1 (au lieu de 0)
changement mineurs :
- changement dans le code (dans la forme)
- prise en compte de la difficulté dans le nombre de points gagnés par les complétions de ligne