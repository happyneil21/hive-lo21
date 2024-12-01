#include "Game.h"
#include "Pieces.h"
#include <algorithm>
using namespace std;

Jeu::Jeu() {  // on va ajouter à la liste des pieces disponible en stock les pieces qu'on veut utiliser pendant la partie
    // là c'est la compo basqiue je crois à veriier
    pieces_disponible.push_back(new ReineAbeille);
    pieces_disponible.push_back(new Scarabee);
    pieces_disponible.push_back(new Scarabee);
    pieces_disponible.push_back(new Araignee);
    pieces_disponible.push_back(new Araignee);
    pieces_disponible.push_back(new Fourmis);
    pieces_disponible.push_back(new Fourmis);
    pieces_disponible.push_back(new Fourmis);
    pieces_disponible.push_back(new Sauterelle);
    pieces_disponible.push_back(new Sauterelle);
    pieces_disponible.push_back(new Sauterelle);
    pieces_disponible.push_back(new Moustique);
    pieces_disponible.push_back(new Moustique);
}

void Jeu::ajouterPiece(Piece* piece, int x, int y) {  // ajouter une piece au Jeu = ajouter une piece au plateau principale en gros (pieces_placees.push_back(piece);)
    auto it = find(pieces_disponible.begin(), pieces_disponible.end(), piece);
    if (it != pieces_disponible.end()) {
        piece->placerPiece(x, y);
        pieces_placees.push_back(piece);
        pieces_disponible.erase(it);
    }
    else {
        std::cout << "La pièce de type " << piece->getType() << " n'est pas disponible." << "endl";
    }
}

void Jeu::deplacerPiece(int index, int newX, int newY) {
    if (index >= 0 && index < pieces_placees.size()) {
        pieces_placees[index]->placerPiece(newX, newY);
    }
}

bool Jeu::GameOver() const {
    return verifConditionVictoire();
}

bool Jeu::verifConditionVictoire() const {
    // Implémenter la logique pour vérifier si la Reine Abeille est entourée
    return false; // Placeholder
}
