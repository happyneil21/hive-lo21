#ifndef CASE_H
#define CASE_H
class Case {
public:
    Case() : coloriee(false), x(0), y(0) {} // Constructeur par défaut
    Case(int x, int y) : coloriee(false), x(x), y(y) {} // Constructeur avec coordonnées
    bool estColoriee() const; // Renvoie vrai si la case est colorée
    void changerEtat();       // Change l'état de la case (colorie ou décolore)
    int abscisse() const {return x;}
    int ordonnee() const {return y;}


private:
    bool coloriee; // État de la case : true si elle est colorée, false sinon
    int x;
    int y;
};



#endif // CASE_H
