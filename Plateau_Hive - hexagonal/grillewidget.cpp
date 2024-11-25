#include "grillewidget.h"
#include <QPainter>
#include <QMouseEvent>

GrilleWidget::GrilleWidget(QWidget *parent)
    : QWidget(parent) {
    // Redimensionner la grille
    grid.resize(rows);
    for (int i = 0; i < rows; ++i) {
        grid[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = Case(i, j); // Initialisation avec coordonnées
        }
    }

    setFixedSize(cols * cellSize, rows * cellSize);
}


void GrilleWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Dessiner chaque case
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QRect cellRect(j * cellSize, i * cellSize, cellSize, cellSize);

            // Remplir la case si elle est coloriée
            if (grid[i][j].estColoriee()) {
                painter.fillRect(cellRect, Qt::black);
            }

            // Dessiner les bords de la case
            painter.drawRect(cellRect);
        }
    }
}
void GrilleWidget::mousePressEvent(QMouseEvent *event) {
    int col = event->pos().x() / cellSize;
    int row = event->pos().y() / cellSize;

    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        grid[row][col].changerEtat();
        update();

        // Émettre le signal avec les coordonnées
        emit caseCliquee(row, col);
    }
}


void GrilleWidget::caseClique(int row, int col) {
    grid[row][col].changerEtat(); // Change l'état de la case cliquée
}





/*
#include "grillewidget.h"
#include <QPainter>
#include <QMouseEvent>

GrilleWidget::GrilleWidget(QWidget *parent)
    : QWidget(parent), grid(rows, QVector<Case>(cols)) { // Initialise la grille avec des objets `Case`
    setFixedSize(cols * cellSize, rows * cellSize);
}

void GrilleWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::black);

    // Dessine la grille
    for (int i = 0; i <= cols; ++i) {
        painter.drawLine(i * cellSize, 0, i * cellSize, rows * cellSize);
    }
    for (int j = 0; j <= rows; ++j) {
        painter.drawLine(0, j * cellSize, cols * cellSize, j * cellSize);
    }

    // Colore les cases sélectionnées
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (grid[row][col].estColoriee()) {
                painter.fillRect(col * cellSize, row * cellSize, cellSize, cellSize, Qt::black);
            }
        }
    }
}
*/
