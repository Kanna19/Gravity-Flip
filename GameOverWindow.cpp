#include "GameOverWindow.h"
#include "Game.h"
#include <QCoreApplication>
#include <QLabel>
#include <QDebug>

extern Game* game;
const int GameOverWindow::EXIT_CODE_REBOOT = 10000;

GameOverWindow::GameOverWindow(QWidget *parent): QMainWindow(parent)
{
    // create the Exit Game Button and set its parent
    m_exitGame = new QPushButton("Exit Game", this);
    m_restartGame = new QPushButton("Restart Game", this);

    // set the size and position of the button
    m_exitGame->setGeometry(QRect(QPoint(350, 375), QSize(200, 50)));
    m_restartGame->setGeometry(QRect(QPoint(350, 300), QSize(200, 50)));

    // connect the button to its appropriate slot to handle key press
    connect(m_exitGame, SIGNAL(released()), this, SLOT(handleExitGame()));
    connect(m_restartGame, SIGNAL(released()), this, SLOT(handleRestartGame()));
}

void GameOverWindow::display(int loser)
{
    // make the game window invisible
    game->setVisible(false);

    // disconnect the timer to stop updating the score and background
    game->timer->disconnect();

    /*
     * 0 is loser -> 1 is winner
     * 1 is loser -> 0 is winner
    */

    int winner = 1 -loser;

    // set the image of the winner
    QLabel* displayWinner = new QLabel(this);
    displayWinner->setPixmap(game->images[winner].
            scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    displayWinner->setGeometry(QRect(QPoint(370, 100), QSize(80, 100)));
    displayWinner->show();

    // set the properties of the text to be displayed
    QLabel* displayText = new QLabel(this);
    displayText->setText(" WINS");
    displayText->setStyleSheet("font: 25px; color: blue");
    displayText->setAlignment(Qt::AlignCenter);
    displayText->setGeometry(QRect(QPoint(450, 100), QSize(75, 100)));
    displayText->show();

    // Display the score if game is singleplayer
    if(game->player_cnt == 1)
    {
        QLabel* gameScoreText1 = new QLabel(this);
        gameScoreText1->setText("Score: ");
        gameScoreText1->setStyleSheet("font: 25px; color: blue");
        gameScoreText1->setAlignment(Qt::AlignCenter);
        gameScoreText1->setGeometry(QRect(QPoint(350, 225), QSize(100, 50)));
        gameScoreText1->show();

        QLabel* gameScoreText2 = new QLabel(this);
        gameScoreText2->setText(QString::number(game->scoreUpdater->getScore()));
        gameScoreText2->setStyleSheet("font: 25px; color: blue");
        gameScoreText2->setAlignment(Qt::AlignCenter);
        gameScoreText2->setGeometry(QRect(QPoint(450, 225), QSize(100, 50)));
        gameScoreText2->show();
    }

    this->resize(1000, 500);
    this->move(0, 0);
    this->setStyleSheet("background-image:url(:/res/objects/acid2.png);");
    this->show();
}

void GameOverWindow::handleExitGame()
{
    this->close();
}

void GameOverWindow::handleRestartGame()
{
    qWarning() << "Restarting...";
    qApp->exit(GameOverWindow::EXIT_CODE_REBOOT);
}
