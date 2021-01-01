#pragma once
#include <vector>
#include <iostream>
#include "part_piece.hpp"
#include "tableau.hpp"
#include <ctime>
#include <cstdlib>
#include <stdio.h>

class piece
{
    private:
        int nbDePiece;
        int num_piece;
        int couleur;
        std::vector<part_piece> parts;
        enum Nom_piece
        {
            I, O, L, J, Z, S
        };

    public:
        piece(): nbDePiece(4)
        {
            srand(time(0));
            num_piece = rand()%6;
            couleur = rand()%9 +1;
        };
        piece(int coul): nbDePiece(4), couleur(coul)
        {
            srand(time(0));
            num_piece = rand()%6;
        };
        piece(int num, int coul): nbDePiece(4), num_piece(num), couleur(coul) {};

        int getndDePiece() const;
        int getnum_piece() const;
        int getcouleur() const;
        std::vector<part_piece> getpieces() const;

        void setcouleur(int coul);
        void setpieces(std::vector<part_piece> blocs);

        void _intit_(tableau* tab);
        bool init_piece_standard(tableau* tab);

        bool place_libre(tableau tab, int lig, int col);
        void mouvement(tableau* tab, const char* direction);
        void rotation();

        void descend(tableau* tab);
        void gauche(tableau* tab);
        void droite(tableau* tab);

        void stop();

        ~piece(){};
};