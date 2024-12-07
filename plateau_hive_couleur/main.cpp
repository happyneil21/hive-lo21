#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QApplication>
#include <QLabel>
#include "grillewidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget mainWindow;
    mainWindow.setWindowTitle("Plateau Hive");

    // Création de la grille
    GrilleWidget *grilleWidget = new GrilleWidget(&mainWindow);

    // Création des boutons de couleur avec une taille carrée
    QPushButton *boutonRouge = new QPushButton();
    boutonRouge->setStyleSheet("background-color: red;");
    boutonRouge->setFixedSize(50, 50);  // Taille carrée

    QPushButton *boutonVert = new QPushButton();
    boutonVert->setStyleSheet("background-color: green;");
    boutonVert->setFixedSize(50, 50);  // Taille carrée

    QPushButton *boutonBleu = new QPushButton();
    boutonBleu->setStyleSheet("background-color: blue;");
    boutonBleu->setFixedSize(50, 50);  // Taille carrée

    QPushButton *boutonJaune = new QPushButton();
    boutonJaune->setStyleSheet("background-color: yellow;");
    boutonJaune->setFixedSize(50, 50);  // Taille carrée

    QPushButton *boutonRose = new QPushButton();
    boutonRose->setStyleSheet("background-color: magenta;");
    boutonRose->setFixedSize(50, 50);  // Taille carrée

    // Création d'un QLabel pour afficher les coordonnées
    QLabel *labelCoordonnees = new QLabel("Coordonnées : (q, r)", &mainWindow);

    // Layout pour les boutons de couleurs (palette)
    QVBoxLayout *paletteLayout = new QVBoxLayout;
    paletteLayout->addWidget(boutonRouge);       // Ajout du bouton rouge
    paletteLayout->addWidget(boutonVert);        // Ajout du bouton vert
    paletteLayout->addWidget(boutonBleu);        // Ajout du bouton bleu
    paletteLayout->addWidget(boutonJaune);       // Ajout du bouton jaune
    paletteLayout->addWidget(boutonRose);        // Ajout du bouton rose
    paletteLayout->addWidget(labelCoordonnees);  // Ajout du label pour les coordonnées

    // Layout principal pour l'agencement horizontal (grille à gauche et palette à droite)
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(grilleWidget);   // Ajout de la grille dans la première colonne
    mainLayout->addLayout(paletteLayout);  // Ajout de la palette dans la deuxième colonne (à droite)

    // Applique le layout principal à la fenêtre principale
    mainWindow.setLayout(mainLayout);
    mainWindow.resize(800, 600);  // Taille de la fenêtre principale

    // Connexion des boutons aux actions de la grille
    QObject::connect(boutonRouge, &QPushButton::clicked, [grilleWidget]() {
        grilleWidget->setCouleurSelectionnee(Qt::red);
    });
    QObject::connect(boutonVert, &QPushButton::clicked, [grilleWidget]() {
        grilleWidget->setCouleurSelectionnee(Qt::green);
    });
    QObject::connect(boutonBleu, &QPushButton::clicked, [grilleWidget]() {
        grilleWidget->setCouleurSelectionnee(Qt::blue);
    });
    QObject::connect(boutonJaune, &QPushButton::clicked, [grilleWidget]() {
        grilleWidget->setCouleurSelectionnee(Qt::yellow);
    });
    QObject::connect(boutonRose, &QPushButton::clicked, [grilleWidget]() {
        grilleWidget->setCouleurSelectionnee(Qt::magenta);
    });

    // Connexion du signal de la grille pour mettre à jour les coordonnées
    QObject::connect(grilleWidget, &GrilleWidget::caseCliquee, [labelCoordonnees](int q, int r, int s) {
        labelCoordonnees->setText(QString("Coordonnées : (%1, %2, %3)").arg(q).arg(r).arg(s));
    });

    mainWindow.show(); // Affiche la fenêtre principale

    return app.exec();
}
