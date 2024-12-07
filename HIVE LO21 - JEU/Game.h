#pragma once

#include <vector>
#include <string>
#include "Pieces.h"
using namespace std;

class Case;
class Piece;

class Joueur {
public:
    Joueur(const string& pseudo) : pseudo(pseudo) {}
    string getPseudo() const { return pseudo; }

private:
    string pseudo;
};

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

    void jouer(); // Nouvelle méthode pour diriger le jeu
    void tourJoueur(Joueur* joueur);
    Piece* choisirPiece(string type_choisi);

private:
    Jeu(); // Constructeur privé pour le Singleton
    ~Jeu();
    Jeu(const Jeu&) = delete;
    Jeu& operator=(const Jeu&) = delete;
    static Jeu* instance; // Pointeur statique vers l'instance unique
    vector<Piece*> pieces_disponible;
    vector<Case> plateau; // pas besoin de pointeur car plus simple et l'objet case n'est pas lourd à manipuler
    bool verifConditionVictoire() const;

    vector<Joueur*> joueurs; // Liste des joueurs en tant que pointeurs
};
