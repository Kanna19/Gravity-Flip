#include "MainWindow.h"
#include "Game.h"
#include <QCoreApplication>

Game *game;

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

    // TODO: connect the slots
    // connect the buttons to the appropriate slots
    connect(m_singlePlayer, SIGNAL(released()), this, SLOT(handleSinglePlayer()));
    connect(m_multiPlayer, SIGNAL(released()), this, SLOT(handleMultiPlayer()));
    connect(m_exitGame, SIGNAL(released()), this, SLOT(handleExitGame()));
}

void MainWindow::display()
{
    this->resize(1000, 500);
    this->setStyleSheet("background-image:url(:/res/objects/acid2.png);");
    this->show();
}

void MainWindow::handleSinglePlayer()
{
    // close the main window
    this->close();

    // open the game
    game = new Game(1);
    game->show();
}

void MainWindow::handleMultiPlayer()
{
    // close the main window
    this->close();

    // open the game
    game = new Game(2);
    game->show();
}

void MainWindow::handleExitGame()
{
    // close the main window
    this->close();
}

