#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Game.h"

using namespace std;

class Piece {
public:
    Piece(const string& type) : type(type), place(false), q(0), r(0), s(0) {} // On construit une pièce uniquement à partir de son type en supposant qu'elle n'est pas sur le plateau dès qu'elle est créée
    virtual ~Piece() {}

    int getQ() const { return q; }
    int getR() const { return r; }
    int getS() const { return s; }
    string getType() const { return type; }
    bool estPlacee() const { return placee; }
    void placerPiece(int q, int r, int s);
    void deplacerPiece(int q, int r, int s);

protected: // Pour donner accès à ces données dans les classes qui héritent de Piece
    int q, r, s; // Coordonnées pour l'attribut position
    string type; // Type de la pièce
    bool placee = false; // Pour savoir si la pièce créée est en jeu ou non
};

class Case {
public:
    Case(int q, int y) : m_q(q), m_r(r), m_s(s), m_piece(nullptr) {} // Une case à par défault pas de pièce placée dessu

    int getQ() const { return m_q; }
    int getR() const { return m_r; }
    int getS() const { return m_s; }
    bool estOccupe() const { return m_piece != nullptr; }
    Piece* getPiece() const { return m_piece; }
    void setPiece(Piece* piece) { m_piece = piece; }
    bool estAdjacente(const vector<Case>& plateau) const;

private:
    int m_q, m_r, m_s;
    Piece* m_piece;
};

class ReineAbeille : public Piece {
public:
    ReineAbeille() : Piece("Reine Abeille") {}
    void deplacerReine(int q, int r, int s, const vector<Case>& plateau);// vecteur qui va prendre en mémoire touts les objets cases du plateau
    bool reineEntourer(const vector<Case>& plateau) const;
private:
    bool estOcupe(int q, int r, int s, const vector<Case>& plateau) const;
};

class Araignee : public Piece {
public:
    Araignee() : Piece("Araignée") {}
    void deplacerAraignee(int q, int r, int s, const vector<Case>& plateau);
private:
    bool estAccessibleEn3cases(int q, int r, int s, const vector<Case>& plateau) const;
    bool estOcupe(int q, int r, int s, const vector<Case>& plateau) const;
};

class Scarabee : public Piece {
public:
    Scarabee() : Piece("Scarabée") {}
    void deplacerScarabee(int q, int r, int s, const vector<Case>& plateau);
private:
    bool estOcupe(int q,int r, int s, const vector<Case>& plateau);
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
