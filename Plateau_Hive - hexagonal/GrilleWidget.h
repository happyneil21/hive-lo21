#ifndef GRILLEWIDGET_H
#define GRILLEWIDGET_H

#include <QWidget>
#include <QVector>
#include "case.h"

class GrilleWidget : public QWidget {
    Q_OBJECT

public:
    explicit GrilleWidget(QWidget *parent = nullptr);
signals:
    void caseCliquee(int x, int y); // Signal émis quand une case est cliquée


protected:
    void paintEvent(QPaintEvent *event) override; // Pour dessiner la grille
    void mousePressEvent(QMouseEvent *event) override;

private:
    int rows = 10;       // Nombre de lignes
    int cols = 10;       // Nombre de colonnes
    int cellSize = 40;   // Taille de chaque cellule en pixels
    QVector<QVector<Case>> grid; // Grille de cases
    void caseClique(int row, int col); // Gère le clic sur une case
};

#endif // GRILLEWIDGET_H

/*
#ifndef GRILLEWIDGET_H
#define GRILLEWIDGET_H

#include <QWidget>
#include <QVector>
#include "case.h"

class GrilleWidget : public QWidget {
    Q_OBJECT

public:
    explicit GrilleWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int rows = 10;      // Nombre de lignes
    int cols = 10;      // Nombre de colonnes
    int cellSize = 40;  // Taille de chaque cellule en pixels
    QVector<QVector<Case>> grid; // Grille de cases

    void caseClique(int row, int col); // Gère le clic sur une case
};

#endif // GRILLEWIDGET_H
*/
