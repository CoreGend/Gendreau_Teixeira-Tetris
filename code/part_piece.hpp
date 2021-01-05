#pragma once
#include "includers.h"

class part_piece
{
    private:
        int ligne, colonne, identifiant, couleur;
        bool mobile;

    public:
        part_piece(int identifiant):
            ligne(0), colonne(0), identifiant(identifiant), couleur(-1), mobile(true)
        {
        };
        part_piece(int lig, int col, int identifiant):
            ligne(lig), colonne(col), identifiant(identifiant), couleur(-1), mobile(true)
        {
        };

        int getligne();
        int getcolonne();
        int getidentifiant();
        int getcouleur();
        int getmobile();

        void setligne(int lig);
        void setcolonne(int col);
        void setidentifiant(int id);
        void setcouleur(int coul);
        void setmobile(bool mob);

        void setcoordonnees(int lig, int col);

        ~part_piece(){};
};
