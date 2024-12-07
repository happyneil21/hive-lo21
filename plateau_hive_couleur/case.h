#ifndef CASE_H
#define CASE_H

#include <QPointF> // Pour gérer les positions graphiques
#include <QColor> // Ajoutez cette ligne dans Case.h
class Case {
public:
    Case(int q, int r) : couleur(Qt::white), q(q), r(r), s(-q - r) {} // Constructeur: ici on construit chaque
                                                                    //case avec 3 coordonnées qui correspondent à 3 axes sur la plateau
    bool estColoriee() const { return coloriee; } //méthode const test de si la case est coloriée ou non
    void changerEtat() { coloriee = !coloriee; } //méthode qui change l'état coloriée de la case à non coloriée et inversement
    QColor couleur;  // Attribut pour stocker la couleur de la case

    int getQ() const { return q; } //nos 3 accesseurs qui renvoient les 3 différentes coordonnées
    int getR() const { return r; }
    int getS() const { return s; }
    void setCouleur(const QColor &couleur) { //méthode qui accède à l'attribut couleur et qui la change en cas d'evnmt mouseclique
        this->couleur = couleur;
    }
    QColor getCouleur() const {
        return couleur;
    }



private:
    int q, r, s; // Coordonnées hexagonales
    bool coloriee; //attributs qui correspond à si la case est coloriée ou non

};

#endif // CASE_H
