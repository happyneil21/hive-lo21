#pragma once

#include <string>

class Piece {
public:
    virtual ~Piece() {}
    void setPosition(int x, int y) {
        this->x = x; this->y = y;
    }
    int getX() const { return x; }
    int getY() const { return y; }

protected:
    int x, y;
};


class ReineAbeille : public Piece {
    // parametrer les d�placements
};

class Araignee : public Piece {
    // parametrer les d�placements
};


class Scarabee : public Piece {
    // parametrer les d�placements
};

class Fourmis : public Piece {
    // parametrer les d�placements
};


class Sauterelle : public Piece {
    // parametrer les d�placements
};


class Moustique : public Piece {
    // parametrer les d�placements
};