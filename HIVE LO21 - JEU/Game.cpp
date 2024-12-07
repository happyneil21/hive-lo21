#include "Game.h"
#include "Pieces.h"
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

Jeu::Jeu() {
    // Initialiser les joueurs avec des allocations dynamiques
    joueurs.push_back(new Joueur("Alice"));
    joueurs.push_back(new Joueur("Bob"));

    // Initialiser vos pièces ici
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

    // Initialiser le plateau de jeu avec des Cases
    for (int x = 0; x < 10; ++x) { // Dimensions d'exemple
        for (int y = 0; y < 10; ++y) {
            plateau.push_back(Case(x, y));
        }
    }
}

Jeu::~Jeu() {
    // Libérer la mémoire des joueurs
    for (auto joueur : joueurs) {
        delete joueur;
    }
    joueurs.clear();
}

// Instance du singleton
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

void Jeu::jouer() {
    int tour = 1;
    while (!GameOver()) {
        Joueur* joueurActuel = joueurs[(tour - 1) % joueurs.size()]; // Alterner les tours
        std::cout << "Tour du joueur " << joueurActuel->getPseudo() << std::endl;
        tourJoueur(joueurActuel);
        ++tour;
    }
    std::cout << "Fin de la partie!" << std::endl;
}

Piece* Jeu::choisirPiece(string type_choisi) {
    for (auto it = pieces_disponible.begin(); it != pieces_disponible.end(); ++it) {
        if ((*it)->getType() == type_choisi) {
            Piece* piece = *it; 
            pieces_disponible.erase(it); // Retirer la pièce du vecteur 
            return piece; 
        } 
    } 
    return nullptr; 
}

void Jeu::tourJoueur(Joueur* joueur) {
    int x, y;
    int action_choisie;
    int type_choisi;
    string type_choisi_str;

    cout << "Veux-tu placer ou déplacer une pièce ? \n 1: Placer\n 2: Déplacer\n";
    cin >> action_choisie;

    switch (action_choisie) {
    case 1: {
        cout << "Quel type de pièce veux-tu placer ?\n 1: Reine Abeille\n 2: Fourmis\n 3: Scarabee\n 4: Sauterelle\n 5: Araignee\n";
        cin >> type_choisi;
        cout << joueur->getPseudo() << ", entrez les coordonnées (x y) pour ajouter une pièce: ";
        cin >> x >> y;
        switch (type_choisi) {
        case 1:
            type_choisi_str = "Reine Abeille";
            break;
        case 2:
            type_choisi_str = "Fourmis";
            break;
        case 3:
            type_choisi_str = "Scarabee";
            break;
        case 4:
            type_choisi_str = "Sauterelle";
            break;
        case 5:
            type_choisi_str = "Araignee";
            break;
        default:
            cout << "Type de pièce invalide." << endl;
            return; // Sortir de la fonction en cas de type invalide
        }

        Piece* piece = choisirPiece(type_choisi_str);
        if (piece != nullptr) {
            ajouterPiece(piece, x, y);
        }
        else {
            cout << "Type sélectionné indisponible !!" << endl;
        }
        break;
    }
    case 2: {
        cout << "Quel type de pièce veux-tu déplacer ?\n 1: Reine Abeille\n 2: Fourmis\n 3: Scarabee\n 4: Sauterelle\n 5: Araignee\n";
        cin >> type_choisi;
        switch (type_choisi) {
        case 1:
            type_choisi_str = "Reine Abeille";
            break;
        case 2:
            type_choisi_str = "Fourmis";
            break;
        case 3:
            type_choisi_str = "Scarabee";
            break;
        case 4:
            type_choisi_str = "Sauterelle";
            break;
        case 5:
            type_choisi_str = "Araignee";
            break;
        default:
            cout << "Type de pièce invalide." << endl;
            return; // Sortir de la fonction en cas de type invalide
        }

        cout << joueur->getPseudo() << ", entrez les coordonnées de la pièce à déplacer (x y) : ";
        cin >> x >> y;

        Piece* piece = nullptr;
        for (Case& c : plateau) {
            if (c.getX() == x && c.getY() == y && c.estOccupe() && c.getPiece()->getType() == type_choisi_str) {
                piece = c.getPiece();
                break;
            }
        }

        if (piece == nullptr) {
            cout << "Aucune pièce trouvée à ces coordonnées." << endl;
            return;
        }

        int newX, newY; // nouvelle coordonnée pour cette foisd éplacer la piece
        cout << joueur->getPseudo() << ", entrez les nouvelles coordonnées (x y) pour déplacer la pièce: ";
        cin >> newX >> newY;
        deplacerPiece(piece, newX, newY);
        break;
    }
    default:
        cout << "Choix invalide." << endl;
        break;
    }
}
