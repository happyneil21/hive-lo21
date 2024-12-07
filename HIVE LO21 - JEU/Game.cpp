#include "Game.h"
#include "Pieces.h"
#include <algorithm>
#include <queue>
using namespace std;

Jeu::Jeu() {
    // Initialize your pieces here
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

    // Initialize the game board (plateau) with Cases
    for (int x = 0; x < 10; ++x) { // Example dimensions
        for (int y = 0; y < 10; ++y) {
            plateau.push_back(Case(x, y));
        }
    }
}

// Singleton instance
Jeu* Jeu::instance = nullptr;

void Jeu::ajouterPiece(Piece* piece, int x, int y) {
    auto it = find(pieces_disponible.begin(), pieces_disponible.end(), piece);
    if (it != pieces_disponible.end()) {
        for (Case& c : plateau) {
            if (c.getX() == x && c.getY() == y && !c.estOccupe()) {
                c.setPiece(piece);
                piece->placerPiece(x, y);
                pieces_disponible.erase(it);
                return;
            }
        }
        std::cout << "La case (" << x << ", " << y << ") est déjà occupée." << std::endl;
    }
    else {
        std::cout << "La pièce de type " << piece->getType() << " n'est pas disponible." << std::endl;
    }
}

void Jeu::deplacerPiece(Piece* piece, int newX, int newY) {
    for (Case& c : plateau) {
        if (c.getPiece() == piece) {
            c.setPiece(nullptr); // Libérer l'ancienne case en mettant le pointeur de pièce à nullptr
            break;
        }
    }

    for (Case& c : plateau) {
        if (c.getX() == newX && c.getY() == newY && !c.estOccupe()) {
            c.setPiece(piece);
            piece->deplacerPiece(newX, newY);
            return;
        }
    }
    std::cout << "La case (" << newX << ", " << newY << ") est déjà occupée." << std::endl;
}

bool Jeu::GameOver() const {
    return verifConditionVictoire();
}

bool Jeu::verifConditionVictoire() const {
    // Implement the logic to check if the Reine Abeille is surrounded
    return false;
}

static const vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

bool Jeu::TouteslesCasessontConnectées(const vector<Case>& plateau) const {
    if (plateau.empty()) return true;

    // Trouver une première case occupée pour commencer
    size_t start = 0;
    while (start < plateau.size() && !plateau[start].estOccupe()) {
        ++start;
    }

    // Si toutes les cases sont vides
    if (start == plateau.size()) return true;

    queue<const Case*> file;
    vector<bool> visités(plateau.size(), false);
    file.push(&plateau[start]);
    visités[start] = true;
    size_t countVisited = 1; // Compte les cases visitées

    while (!file.empty()) {
        const Case* caseCourante = file.front();
        file.pop();

        for (const auto& direction : directions) {
            int adjX = caseCourante->getX() + direction.first;
            int adjY = caseCourante->getY() + direction.second;

            for (size_t i = 0; i < plateau.size(); ++i) {
                if (!visités[i] && plateau[i].getX() == adjX && plateau[i].getY() == adjY && plateau[i].estOccupe()) {
                    visités[i] = true;
                    file.push(&plateau[i]);
                    ++countVisited;
                }
            }
        }
    }

    // Vérifier si toutes les cases occupées ont été visitées
    for (size_t i = 0; i < plateau.size(); ++i) {
        if (plateau[i].estOccupe() && !visités[i]) {
            return false;
        }
    }

    return true;
}
