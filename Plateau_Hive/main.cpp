#include <QApplication>
#include <QMainWindow>
#include "GrilleWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow mainWindow;

    GrilleWidget *grilleWidget = new GrilleWidget();
    mainWindow.setCentralWidget(grilleWidget);
    mainWindow.show();

    return app.exec();
}
