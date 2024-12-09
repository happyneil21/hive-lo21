#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QApplication>
#include <QLabel>
#include "grillewidget.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Fenêtre principale
    QWidget mainWindow;
    mainWindow.setWindowTitle("Plateau Hive");

    // Création de la grille
    GrilleWidget *grilleWidget = new GrilleWidget(&mainWindow);

    // Créer les boutons pour les insectes avec des icônes
    QPushButton *boutonAbeille = new QPushButton();
    boutonAbeille->setIcon(QIcon(":/ressources/abeille.png"));
    boutonAbeille->setIconSize(QSize(50, 50)); // Taille de l'icône
    boutonAbeille->setFixedSize(60, 60);      // Taille totale du bouton

    QPushButton *boutonAraignee = new QPushButton();
    boutonAraignee->setIcon(QIcon(":/ressources/araignee.png"));
    boutonAraignee->setIconSize(QSize(50, 50));
    boutonAraignee->setFixedSize(60, 60);

    QPushButton *boutonFourmi = new QPushButton();
    boutonFourmi->setIcon(QIcon(":/ressources/fourmi.png"));
    boutonFourmi->setIconSize(QSize(50, 50));
    boutonFourmi->setFixedSize(60, 60);

    QPushButton *boutonSauterelle = new QPushButton();
    boutonSauterelle->setIcon(QIcon(":/ressources/sauterelle.png"));
    boutonSauterelle->setIconSize(QSize(50, 50));
    boutonSauterelle->setFixedSize(60, 60);

    QPushButton *boutonScarabee = new QPushButton();
    boutonScarabee->setIcon(QIcon(":/ressources/scarabee.png"));
    boutonScarabee->setIconSize(QSize(50, 50));
    boutonScarabee->setFixedSize(60, 60);

    // Création d'un QLabel pour afficher les coordonnées des cases cliquées
    QLabel *labelCoordonnees = new QLabel("Coordonnées : (q, r)", &mainWindow);

    // Layout vertical pour la barre latérale (palette d'insectes)
    QVBoxLayout *paletteLayout = new QVBoxLayout;
    paletteLayout->addWidget(boutonAbeille);
    paletteLayout->addWidget(boutonAraignee);
    paletteLayout->addWidget(boutonFourmi);
    paletteLayout->addWidget(boutonSauterelle);
    paletteLayout->addWidget(boutonScarabee);
    paletteLayout->addWidget(labelCoordonnees); // Ajoute le label pour les coordonnées
    paletteLayout->addStretch(); // Ajoute un espace flexible en bas

    // Layout horizontal principal (grille à gauche et barre latérale à droite)
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(grilleWidget);   // Ajoute la grille dans la première colonne
    mainLayout->addLayout(paletteLayout);  // Ajoute la palette dans la deuxième colonne (à droite)

    // Applique le layout principal à la fenêtre principale
    mainWindow.setLayout(mainLayout);
    mainWindow.resize(800, 600);  // Taille de la fenêtre principale

    // Connexions des boutons pour définir l'insecte sélectionné dans la grille ( je comprend pas les messages d'erreurs mais ça empêche pas la compil donc bref)
    QObject::connect(boutonAbeille, &QPushButton::clicked, [grilleWidget]() {
        grilleWidget->setInsecteSelectionne("abeille");
    });
    QObject::connect(boutonAraignee, &QPushButton::clicked, [grilleWidget]() {
        grilleWidget->setInsecteSelectionne("araignee");
    });
    QObject::connect(boutonFourmi, &QPushButton::clicked, [grilleWidget]() {
        grilleWidget->setInsecteSelectionne("fourmi");
    });
    QObject::connect(boutonSauterelle, &QPushButton::clicked, [grilleWidget]() {
        grilleWidget->setInsecteSelectionne("sauterelle");
    });
    QObject::connect(boutonScarabee, &QPushButton::clicked, [grilleWidget]() {
        grilleWidget->setInsecteSelectionne("scarabee");
    });

    // Connexion du signal de la grille pour mettre à jour le label avec les coordonnées des cases cliquées
    QObject::connect(grilleWidget, &GrilleWidget::caseCliquee, [labelCoordonnees](int q, int r, int s) {
        labelCoordonnees->setText(QString("Coordonnées : (%1, %2, %3)").arg(q).arg(r).arg(s));
    });

    // Affiche la fenêtre principale
    mainWindow.show();

    return app.exec();
}
