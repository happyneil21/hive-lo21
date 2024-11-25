#include "case.h"



// Méthode pour savoir si la case est coloriée
bool Case::estColoriee() const {
    return coloriee;
}

// Méthode pour changer l'état de la case
void Case::changerEtat() {
    coloriee = !coloriee; // Inverse l'état de la case
}

// Accesseurs des coordonnées (déjà dans `case.h` comme fonctions en ligne)
// int Case::abscisse() const { return x; }
// int Case::ordonnee() const { return y; }
