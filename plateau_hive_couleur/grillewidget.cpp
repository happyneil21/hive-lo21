#include "grillewidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>

GrilleWidget::GrilleWidget(QWidget *parent)
    : QWidget(parent) {
    couleurSelectionnee = Qt::red; // Couleur par défaut
    // Taille de la grille hexagonale
    int radius = 5; // Taille du rayon de la grille (hexagones autour du centre)

    for (int q = -radius; q <= radius; ++q) {
        QList<Case> row; // Chaque rangée de la grille hexagonale
        for (int r = -radius; r <= radius; ++r) { //distribue les coordonnée r
            int s = -q - r; //comme en vrai y'a pas besoin des 3 coordonnées pour construire, on calcule la dernière car pour toutes les cases q+ r+ s = 0
            if (std::abs(s) <= radius) {
                row.append(Case(q, r)); // Ajoute une case à la rangée
            }
        }
        grid.append(row); // Ajoute la rangée à la grille
    }

    setFixedSize(800, 800); // Taille fixe de la fenêtre
}

QPolygon GrilleWidget::createHexagon(int centerX, int centerY, int size) {
    QPolygon hexagon;
    for (int i = 0; i < 6; ++i) {
        // Calcul des points de l'hexagone
        int x = centerX + size * qCos(M_PI / 3 * i);
        int y = centerY + size * qSin(M_PI / 3 * i);
        hexagon << QPoint(x, y);
    }
    return hexagon;  // Retourner le QPolygon
}



void GrilleWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this); // Création de l'objet QPainter pour dessiner
    painter.setRenderHint(QPainter::Antialiasing); // Active l'anti-crénelage pour des dessins plus nets

    // Parcours de toutes les cases de la grille
    for (QList<Case> &row : grid) {
        for (Case &c : row) {
            // Calcul des coordonnées du centre de l'hexagone pour chaque case
            int centerX = width() / 2 + cellSize * (3.0 / 2 * c.getQ());
            int centerY = height() / 2 + cellSize * (std::sqrt(3.0) * (c.getR() + c.getQ() / 2.0));

            // Dessin de l'hexagone avec la couleur actuelle de la case
            QPolygon hexagon = createHexagon(centerX, centerY, cellSize); // Création de l'hexagone
            if (c.couleur.isValid()) {
                painter.setBrush(c.couleur); // Si la couleur de la case est valide, on la choisit
            } else {
                painter.setBrush(Qt::white); // Sinon, on utilise la couleur blanche (case vide)
            }
            painter.setPen(Qt::black); // Tracer le contour en noir
            painter.drawPolygon(hexagon); // Dessin de l'hexagone

            // Affichage des coordonnées à l'intérieur de l'hexagone
            painter.setPen(Qt::black); // Couleur du texte
            //painter.drawText(centerX - 10, centerY + 5, QString("(%1, %2)").arg(c.getQ()).arg(c.getR())); // Coordonnées q, r
        }
    }
}





void GrilleWidget::mousePressEvent(QMouseEvent *event) {
    int xClick = event->x();
    int yClick = event->y();

    for (QList<Case> &row : grid) {  // Parcours des lignes
        for (Case &c : row) {        // Parcours des cases dans chaque ligne
            // Calcul des coordonnées du centre de l'hexagone
            int centerX = width() / 2 + cellSize * (3.0 / 2 * c.getQ());
            int centerY = height() / 2 + cellSize * (std::sqrt(3.0) * (c.getR() + c.getQ() / 2.0));

            // Vérifie si le clic est dans cet hexagone
            if (isPointInHexagon(xClick, yClick, centerX, centerY, cellSize)) {
                c.setCouleur(couleurSelectionnee);  // Applique la couleur sélectionnée
                update();        // Redessine la grille
                emit caseCliquee(c.getQ(), c.getR(), c.getS()); // Émet le signal avec les coordonnées
                return;          // Sortir dès qu'une case est trouvée
            }
        }
    }
}







bool GrilleWidget::isPointInHexagon(int px, int py, int cx, int cy, int size)  {
    // Création des sommets de l'hexagone
    QPolygonF hexagon;
    for (int i = 0; i < 6; ++i) {
        double angle = M_PI / 3 * i; // Angle des sommets
        QPointF point(cx + size * std::cos(angle), cy + size * std::sin(angle));
        hexagon << point;
    }

    // Vérifie si le point (px, py) est dans le polygone
    return hexagon.containsPoint(QPointF(px, py), Qt::OddEvenFill);
}


std::pair<int, int> GrilleWidget::pixelToHex(QPointF point) {
    float q = (2.0 / 3.0 * point.x()) / cellSize;
    float r = (-1.0 / 3.0 * point.x() + sqrt(3.0) / 3.0 * point.y()) / cellSize;

    int qRound = round(q);
    int rRound = round(r);
    int sRound = round(-q - r);

    float qDiff = std::abs(qRound - q);
    float rDiff = std::abs(rRound - r);
    float sDiff = std::abs(sRound - (-q - r));

    if (qDiff > rDiff && qDiff > sDiff) {
        qRound = -rRound - sRound;
    } else if (rDiff > sDiff) {
        rRound = -qRound - sRound;
    }

    return {qRound, rRound};
}


void GrilleWidget::caseClique(int row, int col) {
    grid[row][col].changerEtat(); // Change l'état de la case cliquée
}

QPointF GrilleWidget::hexToPixel(int q, int r) {
    float x = cellSize * 3.0 / 2.0 * q;
    float y = cellSize * sqrt(3.0) * (r + q / 2.0);
    return QPointF(x, y);
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
