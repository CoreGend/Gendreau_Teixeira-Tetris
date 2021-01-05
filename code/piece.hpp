#pragma once
#include "includers.h"
#include "part_piece.hpp"
#include "tableau.hpp"


class piece
{
    private:
        int nbDePiece;
        int num_piece;
        int identifiant;
        std::vector<part_piece> parts;
        enum Nom_piece
        { I, O, L, J, Z, S };

    public:
        piece(): nbDePiece(4)
        {
            srand(time(0));
            //num_piece = rand()%6;
            num_piece = 1;
            identifiant = rand()%1000 +1;
        };
        piece(int id): nbDePiece(4), identifiant(id)
        {
            srand(time(0));
            //num_piece = rand()%6;
            num_piece = 1;
        };
        piece(int num, int id): nbDePiece(4), num_piece(num), identifiant(id) {};

        int getndDePiece() const;
        int getnum_piece() const;
        int getidentifiant() const;
        std::vector<part_piece> getpieces() const;

        void setidentifiant(int id);
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
