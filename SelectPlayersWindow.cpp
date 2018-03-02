#include "SelectPlayersWindow.h"
#include "Game.h"
#include <QPixmap>
#include <QDebug>

Game* game;

SelectPlayersWindow::SelectPlayersWindow(int cnt, QWidget *parent):
    QMainWindow(parent), m_imageCount (4)
{
    // Indicates whether the game is singleplayer or multiplayer
    m_cnt = cnt;

    // Set the desired properties of the text to be displayed
    m_label = new QLabel(this);

    if(cnt == 1)
    {
        m_label->setText("Select Your Player");
    }

    else
    {
        m_label->setText("Select Player 1");
    }

    m_label->setStyleSheet("font: 25px; color: blue");
    m_label->setAlignment(Qt::AlignCenter);
    m_label->setGeometry(QRect(QPoint(250, 100), QSize(400, 100)));
    m_label->show();

    m_playerID.resize(2);
    m_images.resize(m_imageCount);

    for(int i = 0; i < 2; i++)
        m_playerID[i] = 0;

    // Map the signals to the appropriate slots
    m_mapper = new QSignalMapper;

    /*
     * Set the images to be displayed on the buttons
     * and also set their parents
     */

    for(int i = 0; i < m_imageCount; i++)
    {
        m_images[i] = new QPushButton(this);
        m_images[i]->setIcon(QIcon(":res/player/" +QString::number(i +1) +"idle1.png"));
        m_images[i]->setIconSize(QSize(100, 100));

        connect(m_images[i], SIGNAL(released()), m_mapper, SLOT(map()));
        m_mapper->setMapping(m_images[i], i +1);
    }

    // Set the positions and sizes of the push buttons

    const int yPos = 200;
    const int xPosOfFirstImage = 200;

    for(int i = 0; i < m_imageCount; i++)
    {
        m_images[i]->setGeometry(QRect(QPoint(xPosOfFirstImage +(150 *i), yPos), QSize(100, 200)));
    }

    // Show the player images

    for(int i = 0; i < m_imageCount; i++)
    {
        m_images[i]->show();
    }

    connect(m_mapper, SIGNAL(mapped(int)), this, SLOT(setPlayer1ID(int)));
}

void SelectPlayersWindow::display()
{
    // Set the position
    this->resize(1000, 500);
    this->move(0, 0);
    this->setStyleSheet("background-image:url(:/res/objects/acid2.png);");
    this->show();
}

void SelectPlayersWindow::setPlayer1ID(int id)
{
    // Map the selected option to playerIndex = 1
    // Used to represent the character chosen by player 1

    m_playerID[0] = id;

    // Update the display to show the options to select for the 2nd player
    updateDisplay();
}

void SelectPlayersWindow::setPlayer2ID(int id)
{
    // Map the selected option to playerIndex = 2
    // Used to represent the character chosen by player 2

    m_playerID[1] = id;

    // All choices have been made. Start new Game.
    createNewGame();
}

void SelectPlayersWindow::updateDisplay()
{
    // Disconnect the previous mappings of signals to slots
    disconnect(m_mapper, SIGNAL(mapped(int)), this, SLOT(setPlayer1ID(int)));

    // Hide the label and Change the text to be displayed
    m_label->hide();

    for(int i = 0; i < m_imageCount; i++)
    {
        m_images[i]->hide();
        disconnect(m_images[i], SIGNAL(released()), m_mapper, SLOT(map()));
    }

    if(m_cnt == 1)
    {
        m_label->setText("Select Computer");
    }

    else
    {
        m_label->setText("Select Player 2");
    }

    // Show the updated text
    m_label->show();

    /*
    * Show all the images except the previously chosen one and
    * connect their signals to appropriate slots
    */

    for(int i = 0; i < m_imageCount; i++)
    {
        if(i +1 == m_playerID[0])
            continue;

        m_images[i]->show();

        connect(m_images[i], SIGNAL(released()), m_mapper, SLOT(map()));
        m_mapper->setMapping(m_images[i], i +1);
    }

    connect(m_mapper, SIGNAL(mapped(int)), this, SLOT(setPlayer2ID(int)));
}

void SelectPlayersWindow::createNewGame()
{
    // Close this window and start a new game
    this->close();

    // Create a new game with the current player to image mappings
    game = new Game(m_cnt, m_playerID);

    // Start a singleplayer (or) multiplayer game depending on input
    if(m_cnt == 1)
    {
        game->startSinglePlayerGame();
    }

    else
    {
        game->startMultiPlayerGame();
    }

    game->show();
}
