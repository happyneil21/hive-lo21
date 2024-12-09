#ifndef CASE_H
#define CASE_H

#include <QPointF> // Pour gérer les positions graphiques
#include <QColor> // Ajoutez cette ligne dans Case.h
class Case {
public:
    Case(int q, int r) :couleur(Qt::white),q(q), r(r), s(-q - r) {} // Constructeur: ici on construit chaque case avec 3 coordonnées qui correspondent à 3 axes sur la plateau
    QColor couleur;
    int getQ() const { return q; } //nos 3 accesseurs qui renvoient les 3 différentes coordonnées
    int getR() const { return r; }
    int getS() const { return s; }
    void setInsecte(const QString &insecte) { insecteDansLaCase = insecte;}
    QString getInsecte() const { return insecteDansLaCase;}
    QColor getCouleur() const {return couleur;}
    void setCouleur(const QColor &couleur){this->couleur = couleur;}
    void setImageInsecte(const QString &image) { imageInsecte = image;}
    QString getImageInsecte() const {return imageInsecte;}
private:
    QString imageInsecte; // Chemin ou identifiant de l'image de l'insecte
    QString insecteDansLaCase; // Insecte placé dans la case (vide si aucun)
    int q, r, s; // Coordonnées hexagonales

};

#endif // CASE_H
