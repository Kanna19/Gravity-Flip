#include <QApplication>
#include "MainWindow.h"
#include "GameOverWindow.h"

int main(int argc, char *argv[])
{
    int exitCode = 0;

    do
    {
        QApplication a(argc, argv);

        // create and display a main window
        MainWindow* mainWindow = new MainWindow;
        mainWindow->display();

        exitCode = a.exec();

    } while(exitCode == GameOverWindow::EXIT_CODE_REBOOT);

    return exitCode;
}
