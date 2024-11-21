#include "case.h"

Case::Case() : coloriee(false) {} // Initialisation : la case n'est pas colorée au départ

bool Case::estColoriee() const {
    return coloriee;
}

void Case::changerEtat() {
    coloriee = !coloriee; // Inverse l'état de la case
}
