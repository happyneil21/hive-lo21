#pragma once

#include <vector>
#include "Pieces.h"
using namespace std;

class Case;
class Piece;

class Jeu {
public:
    static Jeu* getInstance() {
        if (instance == nullptr) {
            instance = new Jeu();
        }
        return instance;
    }

    void ajouterPiece(Piece* piece, int x, int y);
    void deplacerPiece(Piece* piece, int x, int y);
    bool GameOver() const;
    bool TouteslesCasessontConnectées(const vector<Case>& plateau) const;

private:
    Jeu(); //constructeur privé pour le Singleton
    ~Jeu() {}
    Jeu(const Jeu&) = delete;
    Jeu& operator=(const Jeu&) = delete;
    static Jeu* instance; // Pointeur statique vers l'instance unique
    vector<Piece*> pieces_disponible;
    vector<Case> plateau; // Note: vector<Case> instead of vector<Case*>
    bool verifConditionVictoire() const;
};

class Joueur {
public:

private:
    string pseudo;

};

class Controleur {
public:

private:
};
