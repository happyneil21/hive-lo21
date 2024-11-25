#ifndef PIECES_H
#define PIECES_H

#pragma once

#include <iostream>
#include <stdio.h>
#include <string>

class Piece {
public:
    Piece(const string& type) : type(type) {} ///on construit une pi�ce uniquement � partir de son type en supposant qu'elle n'est pas sur le plateaud�s qu'elle est cr��e
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

protected: ///pour donner acc�s � ces donn�es dans les classes qui h�ritent de Piece
    int x, y; ///coordonn�es pour l'attribut position
    string type; ///type de la pi�ce
    bool placee = false; ///pour savoir si la pi�ce cr��e est en jeu ou non
};


class ReineAbeille : public Piece {
    // parametrer les d�placements
};



class ReineAbeille : public Piece {
public:
    void deplacerReine(int x, int y) {
        if ((x == ReineAbeille.x || x == ReineAbeille.x + 1 || x == ReineAbeille.x - 1) && // Je v�rifie que le Movement demand� est possible selon les r�gles 
            y == ReineAbeille.y || y == ReineAbeille.y + 1 || x == ReineAbeille.y - 1) &&
            !estOcupe(x, y)){  // Il faut aussi rajouter une condition si il y a des cases occup�es ou non
                ReineAbeille.deplacerPiece(x, y); //La fonction deplacerPiecer v�rifira si il y a une pi�ce adjacente
            }
    }
    bool reineEntourer() {
        return  estOcupe(ReineAbeille.x + 1, ReineAbeille.y) &&  //V�rifie si toute les cases autour de la reine sont occup� 
                estOcupe(ReineAbeille.x - 1, ReineAbeille.y) &&
                estOcupe(ReineAbeille.x, ReineAbeille.y + 1) &&
                estOcupe(ReineAbeille.x, ReineAbeille.y - 1) &&
                estOcupe(ReineAbeille.x + 1, ReineAbeille.y + 1) &&
                estOcupe(ReineAbeille.x + 1, ReineAbeille.y - 1); //manque deux diags
    }
};

class Case {
    int m_x, m_y;
    bool m_estOcupe;
public:
    bool getEtat() {
        return m_estOcupe;
    }
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

#endif

