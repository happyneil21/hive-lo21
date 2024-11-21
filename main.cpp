#include <iostream>
#include "Game.h"
#include "Pieces.h"
using namespace std;

int main() {
    Jeu jeu;

    do {
        cout << "debut du jeu";
        /* [rappel règle du jeu] :
        A chaque tour du joueur y a 2 CHOIX: déplacer ou placer une nouvelle pièce */

    } while (!jeu.GameOver());

    return 0;
}
