#include "MainWindow.h"
#include "SelectPlayersWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    // create the required buttons and set their parent to "this"
    m_singlePlayer = new QPushButton("Single Player", this);
    m_multiPlayer = new QPushButton("Multi Player", this);
    m_exitGame = new QPushButton("Exit", this);

    // set the size and position of the buttons
    m_singlePlayer->setGeometry(QRect(QPoint(350, 100), QSize(200, 50)));
    m_multiPlayer->setGeometry(QRect(QPoint(350, 200), QSize(200, 50)));
    m_exitGame->setGeometry(QRect(QPoint(350, 300), QSize(200, 50)));

    // connect the buttons to the appropriate slots
    connect(m_singlePlayer, SIGNAL(released()), this, SLOT(handleSinglePlayer()));
    connect(m_multiPlayer, SIGNAL(released()), this, SLOT(handleMultiPlayer()));
    connect(m_exitGame, SIGNAL(released()), this, SLOT(handleExitGame()));
}

void MainWindow::display()
{
    this->resize(1000, 500);
    this->move(0, 0);
    this->setStyleSheet("background-image:url(:/res/objects/acid2.png);");
    this->show();
}

void MainWindow::handleSinglePlayer()
{
    // close the main window
    this->close();

    // create a new window to select the players
    SelectPlayersWindow *selectPlayersWindow = new SelectPlayersWindow(1, this);
    selectPlayersWindow->display();
}

void MainWindow::handleMultiPlayer()
{
    // close the main window
    this->close();

    // create a new window to select the players
    SelectPlayersWindow *selectPlayersWindow = new SelectPlayersWindow(2, this);
    selectPlayersWindow->display();
}

void MainWindow::handleExitGame()
{
    // close the main window
    this->close();
}

