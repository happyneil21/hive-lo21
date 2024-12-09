#ifndef GRILLEWIDGET_H
#define GRILLEWIDGET_H

#include <QWidget>
#include <QVector>
#include "case.h"

class GrilleWidget : public QWidget {
    Q_OBJECT //maccro

public:
    explicit GrilleWidget(QWidget *parent = nullptr); //constructeur de la grille (explicite pour empêcher les conversion et "sécuriser" le code )
    void bot();
    void setInsecteSelectionne(const QString &insecte) { //juste un ligne de débug pour s'assurer qu'un insecte a été séléctionné sur le panneau latéral
        qDebug() << "Insecte sélectionné :" << insecte;
        insecteSelectionne = insecte;
    }
    QPolygon createHexagon(int centerX, int centerY, int size);
signals:
    void caseCliquee(int q, int r, int s);//signal "la case a été cliquée"
protected:
    void paintEvent(QPaintEvent *event) override; // méthode pour dessiner la grille
    void mousePressEvent(QMouseEvent *event) override; //méthode pour l'évènement quand le clic de la souris est détécté
    std::pair<int, int> pixelToHex(QPointF point);//méthode pour le dessin des hexagones, on doit convertir les coordonées hex en cartésiennes
    bool isPointInHexagon(int px, int py, int cx, int cy, int size);//pour déterminer si un point donné se trouve à l'intérieur d'un hexagone particulier
    QPointF hexToPixel(int q, int r);
private:
    int rows = 10;       // Nombre de lignes
    int cols = 10;       // Nombre de colonnes
    int cellSize = 40;   // Taille de chaque cellule en pixels
    QList<QList<Case>> grid; // Grille de cases (liste de rangées)
    void caseClique(int row, int col); // Gère le clic sur une case
    QString insecteSelectionne; // Insecte actuellement sélectionné (nom du fichier ou type)
    bool isBotTurn;  // Indique si c'est au tour du bot de jouer
    QList<QString> insectesDisponibles; // Liste des insectes pour le bot
    QTimer *botTimer;  // Pour gérer le délai avant le mouvement du bot
};

#endif // GRILLEWIDGET_H

