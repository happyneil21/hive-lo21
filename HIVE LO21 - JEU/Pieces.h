#ifndef PIECES_H
#define PIECES_H

#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Piece {
public:
    Piece(const string& type) : type(type), x(0), y(0) {} // On construit une pièce uniquement à partir de son type en supposant qu'elle n'est pas sur le plateau dès qu'elle est créée
    virtual ~Piece() {}

    int getX() const { return x; }
    int getY() const { return y; }
    string getType() const { return type; }
    bool estPlacee() const { return placee; }

    void placerPiece(int x, int y) {
        if (!placee) {
            this->x = x;
            this->y = y;
            placee = true;
        }
    }
    void deplacerPiece(int x, int y) {
        if (placee) {
            this->x = x;
            this->y = y;
        }
    }

protected: // Pour donner accès à ces données dans les classes qui héritent de Piece
    int x, y; // Coordonnées pour l'attribut position
    string type; // Type de la pièce
    bool placee = false; // Pour savoir si la pièce créée est en jeu ou non
};

class Case {
public:
    Case(int x, int y) : m_x(x), m_y(y), m_estOcupe(false) {}

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    bool estOcupe() const { return m_estOcupe; }
    void occuper() { m_estOcupe = true; }
    void liberer() { m_estOcupe = false; }

    bool estAdjacente(const vector<Case>& plateau) const {
        static const vector<pair<int, int>> directions = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };
        for (const auto& direction : directions) {
            int adjX = m_x + direction.first;
            int adjY = m_y + direction.second;
            for (const auto& c : plateau) {
                if (c.getX() == adjX && c.getY() == adjY && c.estOcupe()) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    int m_x, m_y;
    bool m_estOcupe;
};

class ReineAbeille : public Piece {
public:
    ReineAbeille() : Piece("Reine Abeille") {}
    // def du déplacement !! marche seulement pour un quadrillage
    void deplacerReine(int x, int y, const vector<Case>& plateau) { // vecteur qui va prendre en mémoire touts les objets cases du plateau
        if ((x == this->x || x == this->x + 1 || x == this->x - 1) && // Vérifie que le mouvement demandé est possible selon les règles 
            (y == this->y || y == this->y + 1 || y == this->y - 1) &&
            !estOcupe(x, y, plateau) && Case(x, y).estAdjacente(plateau)) {  // Vérifie si la case est occupée
            this->deplacerPiece(x, y); // La fonction deplacerPiece vérifiera s'il y a une pièce adjacente
        }
    }

    bool reineEntourer(const vector<Case>& plateau) const {
        return  estOcupe(this->x + 1, this->y, plateau) && // Vérifie si toutes les cases autour de la reine sont occupées 
            estOcupe(this->x - 1, this->y, plateau) &&
            estOcupe(this->x, this->y + 1, plateau) &&
            estOcupe(this->x, this->y - 1, plateau) &&
            estOcupe(this->x + 1, this->y + 1, plateau) &&
            estOcupe(this->x + 1, this->y - 1, plateau);
    }

private:
    bool estOcupe(int x, int y, const vector<Case>& plateau) const {
        for (const auto& c : plateau) {
            if (c.getX() == x && c.getY() == y) {
                return c.estOcupe();
            }
        }
        return false;
    }
};

class Araignee : public Piece {
public:
    Araignee() : Piece("Araignée") {}
    void deplacerAraignee(int x, int y, const vector<Case>& plateau) {

    }
private:
    bool estAccessibleEn3cases(int x, int y, const vector<Case>& plateau) const {
        // Logique pour vérifier si la case d'arrivée est accessible en exactement 3 cases 
        // Cette logique dépendra des règles spécifiques de déplacement pour l'araignée 
        int dx = x - this->x;
        int dy = y - this->y;
        if (abs(dx) + abs(dy) != 3) { return false; }
        vector<pair<int, int>> directions = { {1,0}, {-1,0}, {0,1},{1,1}, {0,-1}, {1,-1},{-1,1}, {-1, -1} };
        for (const auto& dir1 : directions) {
            int milX1 = this->x + dir1.first;
            int milY1 = this->y + dir1.second;
            if (estOcupe(milX1, milY1, plateau) && Case(milX1, milY1).estAdjacente(plateau)) continue;
            for (const auto& dir2 : directions) {
                int milX2 = milX1 + dir2.first;
                int milY2 = milY1 + dir2.second;
                if (estOcupe(milX2, milY2, plateau) && Case(milX2, milY2).estAdjacente(plateau)) continue;
                for (const auto& dir3 : directions) {
                    int finalX = milX2 + dir3.first;
                    int finalY = milY2 + dir3.second;
                    if (finalX == x && finalY == y) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool estOcupe(int x, int y, const vector<Case>& plateau) const {
        for (const auto& c : plateau) {
            if (c.getX() == x && c.getY() == y) {
                return c.estOcupe();
            }
        }
        return false;
    }
};

class Scarabee : public Piece {
public:
    Scarabee() : Piece("Scarabée") {}
    // Paramétrer les déplacements
};

class Fourmis : public Piece {
public:
    Fourmis() : Piece("Fourmi") {}
    // Paramétrer les déplacements
};

class Sauterelle : public Piece {
public:
    Sauterelle() : Piece("Sauterelle") {}
    // Paramétrer les déplacements
};

class Moustique : public Piece {
public:
    Moustique() : Piece("Moustique") {}
    // Paramétrer les déplacements
};

#endif
