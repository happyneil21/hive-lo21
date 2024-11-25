#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include "grillewidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Création de la fenêtre principale
    QMainWindow mainWindow;

    // Création du widget central
    QWidget *centralWidget = new QWidget(&mainWindow);

    // Création du layout vertical
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Création de la grille
    GrilleWidget *grilleWidget = new GrilleWidget();

    // Création d'un QLabel pour afficher les coordonnées
    QLabel *labelCoordonnees = new QLabel("Coordonnées : ");
    labelCoordonnees->setAlignment(Qt::AlignCenter);

    // Ajout des widgets au layout
    layout->addWidget(labelCoordonnees);
    layout->addWidget(grilleWidget);

    // Connecter le signal de la grille pour mettre à jour le QLabel
    QObject::connect(grilleWidget, &GrilleWidget::caseCliquee, [&labelCoordonnees](int x, int y) {
        labelCoordonnees->setText(QString("Coordonnées : (%1, %2)").arg(x).arg(y));
    });

    // Définir le widget central pour la fenêtre principale
    mainWindow.setCentralWidget(centralWidget);

    // Afficher la fenêtre principale
    mainWindow.show();

    return app.exec();
}
