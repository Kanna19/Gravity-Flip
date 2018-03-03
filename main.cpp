#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create and display a main window
    MainWindow* mainWindow = new MainWindow;
    mainWindow->display();

    return a.exec();
}
