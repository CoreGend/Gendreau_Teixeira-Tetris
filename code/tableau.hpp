#pragma once
#include "part_piece.hpp"
#include "includers.h"

class tableau
{
    /*
Juste pour être sûr, la longueur correspond à la hauteur du tableau
les lignes et colonnes seront numérotées de 0 à longueur-1 (resp: largeur-1)
    */
    private:
        int hauteur, largeur;
        bool partie_finie;
        std::vector<part_piece> liste;
    
    public:
        tableau(int hauteur, int largeur): hauteur(hauteur), largeur(largeur), partie_finie(0)
        {
            for (int i=0; i < hauteur*largeur; i++)
            {
                part_piece piece_vide(0,0,0);
                liste.push_back(piece_vide);
            }
            qDebug() << "Initialisation effectuée";
        };
        
        int gethauteur() const;
        int getlargeur() const;
        bool getpartie_finie();
        std::vector<part_piece> getliste();

        part_piece& operator () (int i, int j);
        part_piece operator () (int i, int j) const;

        int reconnaissance_ligne();
        void effacement_ligne(int k);
        void verif_fin_partie();
        void changement_position(int prev_lig, int prev_col, int lig, int col, part_piece* pp);

        void affichage();

        ~tableau(){};
};
