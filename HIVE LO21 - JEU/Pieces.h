#ifndef PIECES_H
#define PIECES_H

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Game.h"

using namespace std;

class Piece {
public:
    Piece(const string& type) : type(type), x(0), y(0) {} // On construit une pièce uniquement à partir de son type en supposant qu'elle n'est pas sur le plateau dès qu'elle est créée
    virtual ~Piece() {}

    int getX() const { return x; }
    int getY() const { return y; }
    string getType() const { return type; }
    bool estPlacee() const { return placee; }
    void placerPiece(int x, int y);
    void deplacerPiece(int x, int y);

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

    bool estAdjacente(const vector<Case>& plateau) const;

private:
    int m_x, m_y;
    bool m_estOcupe;
};

class ReineAbeille : public Piece {
public:
    ReineAbeille() : Piece("Reine Abeille") {}
    void deplacerReine(int x, int y, const vector<Case>& plateau);// vecteur qui va prendre en mémoire touts les objets cases du plateau
    bool reineEntourer(const vector<Case>& plateau) const;
private:
    bool estOcupe(int x, int y, const vector<Case>& plateau) const;
};

class Araignee : public Piece {
public:
    Araignee() : Piece("Araignée") {}
    void deplacerAraignee(int x, int y, const vector<Case>& plateau);
private:
    bool estAccessibleEn3cases(int x, int y, const vector<Case>& plateau) const;
    bool estOcupe(int x, int y, const vector<Case>& plateau) const;
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
