#pragma once
#include "includers.h"
#include "part_piece.hpp"
#include "tableau.hpp"
#include "globals.h"

class piece
{
    private:
        int nbDePiece;
        int num_piece;
        int identifiant;
        int rot;    //position de la pièce (en terme de rotation: entier compris entre 0 et 3 inclus)
        std::vector<part_piece> parts;
        enum Nom_piece
        { I, O, L, J, Z, S };

    public:
        piece(piece* p): nbDePiece((*p).getndDePiece()), num_piece((*p).getnum_piece()), identifiant((*p).getidentifiant()), rot(0)
        {
            for (int i=0; i<num_piece; i++)
            {
                part_piece* pp = new part_piece((*p).getpieces()[i]);
                parts.push_back((*pp));
            }
        }
        piece(): nbDePiece(4), rot(0)
        {
            num_piece = rand()%7;
            identifiant = rand()%1000 +1;
        };
        piece(int id): nbDePiece(4), identifiant(id), rot(0)
        {
            num_piece = (seed/id)%7;
        };
        piece(int num, int id): nbDePiece(4), num_piece(num), identifiant(id), rot(0) {};

        int getndDePiece() const;
        int getnum_piece() const;
        int getidentifiant() const;
        std::vector<part_piece> getpieces() const;

        void setidentifiant(int id);
        void setpieces(std::vector<part_piece> blocs);

        void _init_(tableau* tab);
        void placerPiece(tableau* tab, int hauteur, int largeur);
        bool init_piece_standard(tableau* tab);

        bool place_libre(tableau tab, int lig, int col);
        void mouvement(tableau* tab, const char* direction);
        void rotation(tableau* tab); //tourner à droite par défaut, le faire 3x pour tourner à gauche dans un premier temps.

        void descend(tableau* tab);
        void gauche(tableau* tab);
        void droite(tableau* tab);

        void stop();

        ~piece(){};
};
