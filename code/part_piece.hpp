#pragma once

class part_piece
{
    private:
        int ligne, colonne, couleur;
        bool mobile;

    public:
        part_piece(int coul): ligne(0), colonne(0), couleur(coul), mobile(true){};
        part_piece(int lig, int col, int coul): ligne(lig), colonne(col), couleur(coul), mobile(true){};

        int getligne();
        int getcolonne();
        int getcouleur();
        int getmobile();

        void setligne(int lig);
        void setcolonne(int col);
        void setcouleur(int coul);
        void setmobile(bool mob);

        void setcoordonnees(int lig, int col);

        ~part_piece(){};
};