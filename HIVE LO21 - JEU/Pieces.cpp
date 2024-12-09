#include "Pieces.h"


bool Case::estAdjacente(const vector<Case>& plateau) const {
    static const vector<pair<int, int, int>> directions = {
            {0, -1, 1}, {1, -1, 0}, {1, 0, -1}, {0, 1, -1}, {-1, 1, 0}, {-1, 0, +1} //Les 6 directions possibles pour une case/pièce {q, r, s}
    };
    for (const auto& direction : directions) {
        int adjX = m_x + direction.first;
        int adjY = m_y + direction.second;
        for (const auto& c : plateau) {
            if (c.getX() == adjX && c.getY() == adjY && c.estOccupe() == true) {
                return true;
            }
        }
    }
    return false;
}

void ReineAbeille::deplacerReine(int x, int y, const vector<Case>& plateau) {
    if ((x == this->x || x == this->x + 1 || x == this->x - 1) && // Vérifie que le mouvement demandé est possible selon les règles 
        (y == this->y || y == this->y + 1 || y == this->y - 1) &&
        !estOcupe(x, y, plateau) && Case(x, y).estAdjacente(plateau)) {  // Vérifie si la case est occupée
        this->deplacerPiece(x, y); // La fonction deplacerPiece vérifiera s'il y a une pièce adjacente
    }
}

bool ReineAbeille::reineEntourer(const vector<Case>& plateau) const {
        return  estOcupe(this->x + 1, this->y, plateau) && // Vérifie si toutes les cases autour de la reine sont occupées 
            estOcupe(this->x - 1, this->y, plateau) &&
            estOcupe(this->x, this->y + 1, plateau) &&
            estOcupe(this->x, this->y - 1, plateau) &&
            estOcupe(this->x + 1, this->y + 1, plateau) &&
            estOcupe(this->x + 1, this->y - 1, plateau);
    return false;
}

bool ReineAbeille::estOcupe(int x, int y, const vector<Case>& plateau) const {
    for (const auto& c : plateau) {
        if (c.getX() == x && c.getY() == y) {
            return c.estOccupe();
        }
    }
    return false;
}

void Araignee::deplacerAraignee(int x, int y, const vector<Case>& plateau) {
    // Implémentez la logique de déplacement ici
}

bool Araignee::estAccessibleEn3cases(int x, int y, const vector<Case>& plateau) const {
    // Logique pour vérifier si la case d'arrivée est accessible en exactement 3 cases 
    // Cette logique dépendra des règles spécifiques de déplacement pour l'araignée 
    int dx = x - this->x;
    int dy = y - this->y;
    if (abs(dx) + abs(dy) != 3) {
        return false;
    }
    vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {1, 1}, {0, -1}, {1, -1}, {-1, 1}, {-1, -1} };
    for (const auto& dir1 : directions) {
        int milX1 = this->x + dir1.first;
        int milY1 = this->y + dir1.second;
        if (estOcupe(milX1, milY1, plateau) && Case(milX1, milY1).estAdjacente(plateau) && Jeu::getInstance()->TouteslesCasessontConnectées(plateau)) continue;
        for (const auto& dir2 : directions) {
            int milX2 = milX1 + dir2.first;
            int milY2 = milY1 + dir2.second;
            if (estOcupe(milX2, milY2, plateau) && Case(milX2, milY2).estAdjacente(plateau) && Jeu::getInstance()->TouteslesCasessontConnectées(plateau)) continue;
            for (const auto& dir3 : directions) {
                int finalX = milX2 + dir3.first;
                int finalY = milY2 + dir3.second;
                if (finalX == x && finalY == y && Jeu::getInstance()->TouteslesCasessontConnectées(plateau)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Araignee::estOcupe(int x, int y, const vector<Case>& plateau) const {
    for (const auto& c : plateau) {
        if (c.getX() == x && c.getY() == y) {
            return c.estOccupe();
        }
    }
    return false;
}

void Piece::placerPiece(int q, int r, int s) {
    if (!placee) {
        this->q = q;
        this->r = r;
        this->s = s;
        placee = true;
    }
}

void Piece::deplacerPiece(int x, int y) {
    if (placee) {
        this->q = q;
        this->r = r;
        this->s = s;
    }
}
