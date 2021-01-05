#include "tableau.hpp"
#include "part_piece.hpp"


int part_piece::getligne() {
    return this->ligne;
}

int part_piece::getcolonne() {
    return this->colonne;
}
int part_piece::getidentifiant() {
    return this->identifiant;
}
int part_piece::getcouleur(){
    return this->couleur;
}
int part_piece::getmobile() {
    return this->mobile;
}

void part_piece::setligne(int lig) {
    ligne = lig;
}
void part_piece::setcolonne(int col) {
    colonne = col;
}
void part_piece::setidentifiant(int id) {
    identifiant = id;
}
void part_piece::setcouleur(int coul){
    couleur = coul;
}
void part_piece::setmobile(bool mob) {
    mobile = mob;
}

void part_piece::setcoordonnees(int lig, int col){
    ligne = lig;
    colonne = col;
}
