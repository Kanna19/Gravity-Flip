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

    int winner = 1;

    if(loser == 1)
    {
        winner = 2;
    }

    // set the image of the winner
    QLabel* displayWinner = new QLabel(this);
    displayWinner->setPixmap(game->images[winner -1].
            scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    displayWinner->setGeometry(QRect(QPoint(370, 200), QSize(80, 100)));
    displayWinner->show();

    // set the properties of the text to be displayed
    QLabel* displayText = new QLabel(this);
    displayText->setText(" WINS");
    displayText->setStyleSheet("font: 25px; color: blue");
    displayText->setAlignment(Qt::AlignCenter);
    displayText->setGeometry(QRect(QPoint(450, 200), QSize(75, 100)));
    displayText->show();

    this->resize(1000, 500);
    this->move(0, 0);
    this->setStyleSheet("background-image:url(:/res/objects/acid2.png);");
    this->show();
}

void GameOverWindow::handleExitGame()
{
    this->close();
}
