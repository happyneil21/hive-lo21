#include <iostream>
#include "Game.h"
#include "Pieces.h"
using namespace std;

int main() {
    Jeu jeu;

    do {
        cout << "debut du jeu";
        /* [rappel r�gle du jeu] :
        A chaque tour du joueur y a 2 CHOIX: d�placer ou placer une nouvelle pi�ce */

    } while (!jeu.GameOver());

    return 0;
}
