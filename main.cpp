#include <QApplication>
#include "MainWindow.h"
#include "GameOverWindow.h"
#include "BackgroundMusic.h"

int main(int argc, char *argv[])
{
    int exitCode = 0;

    do
    {
        QApplication a(argc, argv);

        // Create and display a main window
        MainWindow* mainWindow = new MainWindow;
        mainWindow->display();

        // Check the value of the exit code to know whether reboot was selected
        exitCode = a.exec();

    } while(exitCode == GameOverWindow::EXIT_CODE_REBOOT);

    return exitCode;
}
