#ifndef CASE_H
#define CASE_H

class Case {
public:
    Case(); // Constructeur par défaut
    bool estColoriee() const; // Renvoie vrai si la case est colorée
    void changerEtat();       // Change l'état de la case (colorie ou décolore)

private:
    bool coloriee; // État de la case : true si elle est colorée, false sinon
};

#endif // CASE_H
