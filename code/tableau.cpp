#include "tableau.hpp"
#include "part_piece.hpp"
#include "includers.h"

int tableau::gethauteur() const {return this->hauteur;}
int tableau::getlargeur() const {return this->largeur;}
bool tableau::getpartie_finie() {return this->partie_finie;}
std::vector<part_piece> tableau::getliste() {return this->liste;}

part_piece& tableau::operator () (int i, int j)
{
    return liste[i*largeur+j];
};

part_piece tableau::operator () (int i, int j) const
{
    return liste[i*largeur+j];
};

void tableau::affichage()
{
    for (int i=0; i<hauteur; i++)
    {
        for (int j=0; j<largeur; j++)
        {
            qDebug() << (*this)(i,j).getcouleur() << " ";
        }
   //     std::cout << std::endl;
    }
};

void tableau::changement_position(int prev_lig, int prev_col, int lig, int col, part_piece* pp)
{
    //part_piece p_piece = (*this)(prev_lig, prev_col);
    pp->setcoordonnees(lig, col);
    (*this)(lig,col) = *pp;
    part_piece piece_zero(0, 0, 0);
    (*this)(prev_lig,prev_col) = piece_zero;
    //std::cout << "Changement de position de la piece " << prev_lig << "," << prev_col << " vers la position " << lig << "," << col << std::endl;
}

int tableau::reconnaissance_ligne()
{
    //Renvoie l'indice de la ligne pleine si elle existe, -1 sinon.
    //Ne detecte qu'une seule ligne, il faudra donc rappeler la fonction jusqu'à ce qu'elle ne détecte plus rien...
    for (int i=0; i<hauteur; i++)
    {
        int j=0;
        int ligne_pleine = 1;
        while (j<largeur && ligne_pleine)
        {
            if ((*this)(i,j).getcolonne() == 0) ligne_pleine = 0;
            j++;
        }
        if (ligne_pleine) return i;
    }
    return -1;
};

void tableau::effacement_ligne(int k)
{
    //Il faudrait libérer l'espace des parties de pièces sur la ligne correspondantes avent de tout faire descendre....
    if (k>0)
    {
        for (int j=0; j<largeur; j++)
        {
            int i = k-1;
            while (i>=0 && (*this)(i,j).getcolonne() != -1)
            {
                this->changement_position(i,j,i+1,j, &(*this)(i,j));
                i--;
            }
        }
    }
};

void tableau::verif_fin_partie()
{
    /*pour le moment la partie se termine quand il y a un bout de piece sur la 2e ligne...
    Car la 1e ligne est réservé aux apparitions de pièce si la 3e ligne est occuppée. */
    int j = 0;
    while (j<largeur && !partie_finie)
    {
        if ((*this)(1,j).getcouleur() != 0) partie_finie = 1;
        j++;
    }
};
