#include "Pieces.h"


bool Case::estAdjacente(const vector<Case>& plateau) const {
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

void ReineAbeille::deplacerReine(int x, int y, const vector<Case>& plateau) {
    if ((x == this->x || x == this->x + 1 || x == this->x - 1) && // V�rifie que le mouvement demand� est possible selon les r�gles 
        (y == this->y || y == this->y + 1 || y == this->y - 1) &&
        !estOcupe(x, y, plateau) && Case(x, y).estAdjacente(plateau)) {  // V�rifie si la case est occup�e
        this->deplacerPiece(x, y); // La fonction deplacerPiece v�rifiera s'il y a une pi�ce adjacente
    }
}

bool ReineAbeille::reineEntourer(const vector<Case>& plateau) const {
        return  estOcupe(this->x + 1, this->y, plateau) && // V�rifie si toutes les cases autour de la reine sont occup�es 
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
            return c.estOcupe();
        }
    }
    return false;
}

void Araignee::deplacerAraignee(int x, int y, const vector<Case>& plateau) {
    // Impl�mentez la logique de d�placement ici
}

bool Araignee::estAccessibleEn3cases(int x, int y, const vector<Case>& plateau) const {
    // Logique pour v�rifier si la case d'arriv�e est accessible en exactement 3 cases 
    // Cette logique d�pendra des r�gles sp�cifiques de d�placement pour l'araign�e 
    int dx = x - this->x;
    int dy = y - this->y;
    if (abs(dx) + abs(dy) != 3) {
        return false;
    }
    vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {1, 1}, {0, -1}, {1, -1}, {-1, 1}, {-1, -1} };
    for (const auto& dir1 : directions) {
        int milX1 = this->x + dir1.first;
        int milY1 = this->y + dir1.second;
        if (estOcupe(milX1, milY1, plateau) && Case(milX1, milY1).estAdjacente(plateau) && Jeu::getInstance()->TouteslesCasessontConnect�es(plateau)) continue;
        for (const auto& dir2 : directions) {
            int milX2 = milX1 + dir2.first;
            int milY2 = milY1 + dir2.second;
            if (estOcupe(milX2, milY2, plateau) && Case(milX2, milY2).estAdjacente(plateau) && Jeu::getInstance()->TouteslesCasessontConnect�es(plateau)) continue;
            for (const auto& dir3 : directions) {
                int finalX = milX2 + dir3.first;
                int finalY = milY2 + dir3.second;
                if (finalX == x && finalY == y && Jeu::getInstance()->TouteslesCasessontConnect�es(plateau)) {
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
            return c.estOcupe();
        }
    }
    return false;
}

void Piece::placerPiece(int x, int y) {
    if (!placee) {
        this->x = x;
        this->y = y;
        placee = true;
    }
}

void Piece::deplacerPiece(int x, int y) {
    if (placee) {
        this->x = x;
        this->y = y;
    }
}
