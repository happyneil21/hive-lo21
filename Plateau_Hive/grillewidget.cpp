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

void GrilleWidget::mousePressEvent(QMouseEvent *event) {
    int row = event->y() / cellSize;
    int col = event->x() / cellSize;

    // Vérifie si la position est dans la grille
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        caseClique(row, col);
        update(); // Redessine la grille après modification
    }
}

void GrilleWidget::caseClique(int row, int col) {
    grid[row][col].changerEtat(); // Change l'état de la case cliquée
}
