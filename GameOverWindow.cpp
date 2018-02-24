#include "GameOverWindow.h"
#include "Game.h"
#include <QCoreApplication>
#include <QLabel>

extern Game* game;

GameOverWindow::GameOverWindow(QWidget *parent): QMainWindow(parent)
{
    // create the Exit Game Button and set its parent
    m_exitGame = new QPushButton("Exit Game", this);


    // set the size and position of the button
    m_exitGame->setGeometry(QRect(QPoint(350, 350), QSize(200, 50)));

    // connect the button to its appropriate slot to handle key press
    connect(m_exitGame, SIGNAL(released()), this, SLOT(handleExitGame()));
}

void GameOverWindow::display(int loser)
{
    // make the game window invisible
    game->setVisible(false);

    QLabel *label = new QLabel(this);

    // Set the display text appropriately
    if(game->player_cnt == 1)
    {
        if(loser == 1)
        {
            label->setText("YOU LOSE");
        }

        else
        {
            label->setText("YOU WIN");
        }
    }

    else
    {
        if(loser == 1)
        {
            label->setText("Player 2 Wins");
        }

        else
        {
            label->setText("Player 1 Wins");
        }
    }

    // Set the Properties of the Display Text

    //label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setStyleSheet("font: 25px; color: blue");
    label->setAlignment(Qt::AlignCenter);
    label->setGeometry(QRect(QPoint(250, 200), QSize(400, 100)));
    label->show();

    this->resize(1000, 500);
    this->move(0, 0);
    this->setStyleSheet("background-image:url(:/res/objects/acid2.png);");
    this->show();
}

void GameOverWindow::handleExitGame()
{
    this->close();
}
