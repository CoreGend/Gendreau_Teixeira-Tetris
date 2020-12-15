/* CONTIENT TOUS LES HEADERS DES CLASSES */


class tableau{
private:
    int longueur; int largeur;
    bool partie_finie;
    int* liste;

public:
    tableau(int longueur, int largeur): longueur(0), largeur(0), partie_finie(0)

    void init(int longueur, int largeur);
    void reconnaissance_ligne();
    void effacement_ligne();
    void reconnaissance_colonne();

    ~tableau();
};

/* tableau
parametres :
	entier longueur, largeur
	booleen 'partie finie'

methodes :
	constructeur avec la taille : fait appel a la fonction initialisation

	initialisation
		allocation memoire + remplissage initial (pointeurs NULL partout)

	(descendre ?
		fait descendre toutes les lignes )

	reconnaissance de ligne

	effacement de ligne
		efface une ligne + appel a descendre OU inclut une descente

	reconnaissance de colonne
		on verifie que la ligne du haut-3 (4 lignes de depassement)
		ne contient que des vecteurs nuls OU mouvants
		actualise partie finie

	// convertir coordonee a voir selon structure choisie - liste de liste ou une liste
	//	convertit une coordonnee 'brute' en ligne/colonne ?
	//		case 156 => x = y =

reconnaissance de ligne ?
OUI : effacement de ligne puis descente */


class partie_piece{
private:
    int ligne; int colonne;
    bool mobile;
    int couleur; //a voir le types selon QT

public:
    partie_piece(int ligne, int colonne, int couleur):
        ligne(0), colonne(0), mobile(0), couleur(0);

    void changement_position();
    void recup_coordonnee();
    void changement_couleur();

    ~partie_piece();
};
/*-> partie de piece fixe
parametres :
	coordonee
	booleen mouvant //caracterise si elle est mobile ou pas
	couleur

Methodes :
	Constructeur avec une position et une couleur
	Changement de position
		met a jour sa coordonnee et la place de son pointeur dans le tableau
	Recuperer coordonnee
		renvoie sa coordonnee dans le tableau (pour rotation ou mouvement)
	Changement de couleur
		change de couleur (effacement de ligne pour le style, un petit clignotement)
*/


class piece{
private:
    int nbDePiece;
    (vecteur) pieces;

public:

    void nouvelle_piece(void);
    void mouvement(void);
    void rotation(void);
};
/*-> piece
parametres :
	int nbDePiece
	vecteur [Piece au centre, autres pieces]

methodes :
	- nouvelle piece
		definit type (= couleur), cree la piece au centre et les pieces autour en
		fonction d'un package contenu dans un fichier annexe
	- mouvement
		appelee tous les n-actualisations => on peut tourner 4 fois la pieces avant
qu'elle descende
		si une case non vide en dessous d'une de ses parties, elle se bloque
	- rotation
		pour chaque piece elle compare la coordonnee de la piece au centre avec la piece courante
		effectue la rotation
		verifie qu'elle a la place de tourner

*/
