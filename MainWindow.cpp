#include "MainWindow.h"
#include "Game.h"

#include <QCoreApplication>

Game *game;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    // create the required buttons and set their parent to "this"
    m_startGame= new QPushButton("Start", this);
    m_exitGame = new QPushButton("Exit", this);

    // set the size and position of the buttons
    m_startGame->setGeometry(QRect(QPoint(350, 100), QSize(200, 50)));
    m_exitGame->setGeometry(QRect(QPoint(350, 300), QSize(200, 50)));

    // connect the buttons to the appropriate slots
    connect(m_startGame, SIGNAL(released()), this, SLOT(handleStartGame()));
    connect(m_exitGame, SIGNAL(released()), this, SLOT(handleExitGame()));
}

void MainWindow::display()
{
    this->resize(1000, 500);
    this->setStyleSheet("background-image:url(:/res/objects/acid2.png);");
    this->show();
}

void MainWindow::handleStartGame()
{
    // close the main window
    this->close();

    // open the game
    game = new Game();
    game->show();
}

void MainWindow::handleExitGame()
{
    // close the main window
    this->close();
}

