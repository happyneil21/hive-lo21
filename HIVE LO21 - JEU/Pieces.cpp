#include "Pieces.h"


bool Case::estAdjacente(const vector<Case>& plateau) const {
    static const vector<pair<int, int, int>> directions = {
            {0, -1, 1}, {1, -1, 0}, {1, 0, -1}, {0, 1, -1}, {-1, 1, 0}, {-1, 0, +1} //Les 6 directions possibles pour une case/pièce {q, r, s}
    };
    for (const auto& direction : directions) {
        int adjQ = m_q + direction.first;
        int adjR = m_r + direction.second;
        int adjS = m_s + direction.third;
        for (const auto& c : plateau) { 
            if (c.getQ() == adjQ && c.getR() == adjR && c.getS() == adjS && c.estOccupe() == true) {
                return true;
            }
        }
    }
    return false;
}

void ReineAbeille::deplacerReine(int q, int r, int s, const vector<Case>& plateau) {
    if ((q == this->q || q == this->q + 1 || q == this->q - 1) && // Vérifie que le mouvement demandé est possible selon les règles 
        (r == this->r || r == this->r + 1 || r == this->r - 1) &&
        (s == this->s || s == this->s + 1 || s == this->s - 1) &&
        !estOcupe(q, r, s, plateau) && Case(q, r, s).estAdjacente(plateau)) {  // Vérifie si la case est occupée
        this->deplacerPiece(q, r, s); // La fonction deplacerPiece vérifiera s'il y a une pièce adjacente
    }
}

bool ReineAbeille::reineEntourer(const vector<Case>& plateau) const {
        return  estOcupe(this->q, this->r-1, this->s+1, plateau) && // Vérifie si toutes les cases autour de la reine sont occupées 
            estOcupe(this->q+1, this->r-1, this->s, plateau) &&
            estOcupe(this->q+1, this->r, this->s-1, plateau) &&
            estOcupe(this->q, this->r+1, this->s-1, plateau) &&
            estOcupe(this->q-1, this->r+1, this->s, plateau) &&
            estOcupe(this->q-1, this->r, this->s+1, plateau);
    //return false; return de trop
}

bool ReineAbeille::estOcupe(int q, int r, int s, const vector<Case>& plateau) const {
    for (const auto& c : plateau) {
        if (c.getQ() == q && c.getR() == r && c.getS() == s) {
            return c.estOccupe();
        }
    }
    return false;
}

void Araignee::deplacerAraignee(int q, int r,, int s, const vector<Case>& plateau) {
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

bool Araignee::estOcupe(int q, int r, int s, const vector<Case>& plateau) const {
    for (const auto& c : plateau) {
        if (c.getQ() == q && c.getR() == r && c.getS() == s) {
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
