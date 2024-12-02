#pragma once

#include <vector>
#include "Pieces.h"
using namespace std;

class Jeu {
public:
    Jeu();
    void ajouterPiece(Piece* piece, int x, int y);
    void deplacerPiece(int index, int x, int y);
    bool GameOver() const;

private:
    vector<Piece*> pieces_placees;
    vector <Piece*> pieces_disponible;
    vector <Case*> plateau;
    bool verifConditionVictoire() const;
};
