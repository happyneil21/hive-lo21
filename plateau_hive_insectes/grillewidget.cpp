#include "grillewidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>
#include <cstdlib>   // Pour std::rand()
#include <ctime>     // Pour initialiser la graine de std::rand()
#include <QTimer>
#include <QRandomGenerator>




GrilleWidget::GrilleWidget(QWidget *parent)
    : QWidget(parent), insecteSelectionne(""), isBotTurn(false) {  // Initialisation des variables

    // Initialisation des insectes disponibles pour le bot afin qu'il pioche aléatoirement
    insectesDisponibles = {"abeille", "araignee", "fourmi", "sauterelle", "scarabee"};

    int radius = 5;  // Taille du rayon de la grille (hexagones autour du centre)

    for (int q = -radius; q <= radius; ++q) {
        QList<Case> row; // Chaque rangée de la grille hexagonale
        for (int r = -radius; r <= radius; ++r) { // Distribue les coordonnées r
            int s = -q - r;  // Calcul de s comme la somme doit être 0 pour chaque case (q + r + s = 0)
            if (std::abs(s) <= radius) {
                row.append(Case(q, r));  // Ajoute une case à la rangée
            }
        }
        grid.append(row);  // Ajoute la rangée à la grille
    }

    // Initialisation du timer pour le bot
    botTimer = new QTimer(this);
    connect(botTimer, &QTimer::timeout, this, &GrilleWidget::bot);  //en gros ici on connecte la fin du timer et le jeu du bot

    setFixedSize(900, 900);  // Taille fixe de la fenêtre
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



void GrilleWidget::paintEvent(QPaintEvent *event) { //pas la peine d'enlever le paramètre, ça met encore plus d'erreurs qui empêchent la compilation donc laissez le là
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Parcourir chaque rangée et chaque case de la grille
    for (QList<Case> &row : grid) {
        for (Case &c : row) {
            // Calcul des coordonnées du centre de la case
            int centerX = width() / 2 + cellSize * (3.0 / 2 * c.getQ());
            int centerY = height() / 2 + cellSize * (std::sqrt(3.0) * (c.getR() + c.getQ() / 2.0));

            QPolygon hexagon = createHexagon(centerX, centerY, cellSize); //on dessine

            // Si la case est grisée (jouée par le bot), on applique une couleur gris clair
            if (c.getCouleur() == Qt::gray) {
                painter.setBrush(QBrush(Qt::gray));  // Griser la case
            } else {
                painter.setBrush(QBrush(Qt::white)); // Couleur par défaut
            }

            painter.setPen(Qt::black);  // Tracer la bordure
            painter.drawPolygon(hexagon);  // Dessiner l'hexagone

            // Dessiner l'insecte si la case est occupée
            if (!c.getInsecte().isEmpty()) {
                QPixmap insectePixmap(":/ressources/" + c.getInsecte() + ".png");
                if (!insectePixmap.isNull()) {
                    // Ajuster la taille et la position de l'image
                    int imageSize = cellSize - 10; // Taille légèrement plus petite que la case
                    int imageX = centerX - imageSize / 2;
                    int imageY = centerY - imageSize / 2;
                    painter.drawPixmap(imageX, imageY, imageSize, imageSize, insectePixmap);
                } else {
                    qDebug() << "Erreur : Image non trouvée pour " << c.getInsecte();
                }
            }
        }
    }
}

void GrilleWidget::mousePressEvent(QMouseEvent *event) {
    int xClick = event->x(); //pareil ici j'ai pas compris les erreurs, mais ça empêche pas la compilation donc bon...
    int yClick = event->y();

    // Si c'est le tour du bot, on ne permet pas au joueur de jouer
    if (isBotTurn) {
        return; // Bloque les clics du joueur pendant le tour du bot
    }

    for (QList<Case> &row : grid) {  // Parcours des lignes
        for (Case &c : row) {        // Parcours des cases dans chaque ligne
            int centerX = width() / 2 + cellSize * (3.0 / 2 * c.getQ());
            int centerY = height() / 2 + cellSize * (std::sqrt(3.0) * (c.getR() + c.getQ() / 2.0));

            if (isPointInHexagon(xClick, yClick, centerX, centerY, cellSize)) {
                if (c.getInsecte().isEmpty()) {  // Assure-toi que la case est vide
                    c.setInsecte(insecteSelectionne);  // Applique l'insecte sélectionné à la case
                    update();  // Redessine la grille

                    isBotTurn = true;  // Passer au tour du bot
                    botTimer->start(1000);  // Attendre 1 seconde avant que le bot joue

                }
                return;  // Sort du traitement après avoir trouvé la case
            }
        }
    }
}


void GrilleWidget::bot() {

    if (insectesDisponibles.isEmpty()) return;// Vérifier s'il reste des insectes disponibles

    QString insecteBot = insectesDisponibles[QRandomGenerator::global()->bounded(insectesDisponibles.size())];// Sélectionner un insecte aléatoire

    // Chercher une case aléatoire non occupée
    QVector<Case*> casesLibres; // Liste des cases libres

    for (QList<Case> &row : grid) {
        for (Case &c : row) {
            if (c.getInsecte().isEmpty()) { // Vérifie si la case est vide
                casesLibres.append(&c);
            }
        }
    }

    if (casesLibres.isEmpty()) return; // Si aucune case n'est libre, le bot ne peut pas jouer

    Case *caseChoisie = casesLibres[QRandomGenerator::global()->bounded(casesLibres.size())]; // Sélectionner une case libre au hasard

    caseChoisie->setInsecte(insecteBot);  // Placer l'insecte

    caseChoisie->setCouleur(Qt::gray);   // Griser la case

    update(); // Redessiner la grille

    isBotTurn = false;// Passer le tour au joueur

    botTimer->stop();// Arrêter le timer
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


std::pair<int, int> GrilleWidget::pixelToHex(QPointF point) { //cette fonction est pas intéressante pour vous, laissez là
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


QPointF GrilleWidget::hexToPixel(int q, int r) { //pareil
    float x = cellSize * 3.0 / 2.0 * q;
    float y = cellSize * sqrt(3.0) * (r + q / 2.0);
    return QPointF(x, y);
}



