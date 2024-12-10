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
    if(estAccessibleEn3cases(q,r,s,plateau)){
        this->deplacerPiece(q,r,s,plateau);
    }
}

bool Araignee::estAccessibleEn3cases(int q, int r, int s, const vector<Case>& plateau) const {
    // Logique pour vérifier si la case d'arrivée est accessible en exactement 3 mouvements
    // Les directions possibles dans un plateau hexagonal (axial coordinates)
    static const vector<pair<int, int, int>> directions = {
            {0, -1, 1}, {1, -1, 0}, {1, 0, -1}, {0, 1, -1}, {-1, 1, 0}, {-1, 0, +1} //Les 6 directions possibles pour une case/pièce {q, r, s}
    };

    auto estOccupe = [](int q, int r, const vector<Case>& plateau) -> bool {
        for (const auto& c : plateau) {
            if (c.getQ() == q && c.getR() == r) {
                return c.estOcupe();
            }
        }
        return false;
    };

    for (const auto& dir1 : directions) {
        int q1 = this->q + dir1.first;
        int r1 = this->r + dir1.second;
        int s1 = this->s + dir1.third;

        if (!estOccupe(q1, r1, plateau)) continue;

        for (const auto& dir2 : directions) {
            int q2 = q1 + dir2.first;
            int r2 = r1 + dir2.second;
            int s2 = s1 + dir2.third;

            if (!estOccupe(q2, r2, plateau)) continue;

            for (const auto& dir3 : directions) {
                int finalQ = q2 + dir3.first;
                int finalR = r2 + dir3.second;
                int finalS = s2 + dir3.third

                if (finalQ == q && finalR == r && finalS == s) {
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

void Scarabee::deplacerScarabee(int q, int r, int s, const vector<Case>& plateau){
        if ((q == this->q || q == this->q + 1 || q == this->q - 1) && // Vérifie que le mouvement demandé est possible selon les règles 
        (r == this->r || r == this->r + 1 || r == this->r - 1) &&
        (s == this->s || s == this->s + 1 || s == this->s - 1) &&
        Case(q, r, s).estAdjacente(plateau)) {  //On vérifie juste la case est adjacentes
        this->deplacerPiece(q, r, s); // La fonction deplacerPiece vérifiera s'il y a une pièce adjacente
    }
}

bool Scarabee::estOcupe(int q,int r, int s, const vector<Case>& plateau){
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
