#include "InstructionWindow.h"
#include "SelectPlayersWindow.h"
#include <QLabel>
#include <QPixmap>
#include <QDebug>

InstructionWindow::InstructionWindow(GameType type, QWidget *parent):
    QMainWindow(parent)
{
    // create the required buttons and set their parent to "this"
    m_enterGame = new CustomButton("Enter", this);

    // set the size and position of the buttons
    m_enterGame->setGeometry(QRect(QPoint(400, 400), QSize(200, 50)));

    // connect the buttons to the appropriate slots
    connect(m_enterGame,SIGNAL(pressed()), m_enterGame, SLOT(changeColor()));
    connect(m_enterGame, SIGNAL(released()), this, SLOT(handleEnterGame()));

    m_type = type;

    // Set the desired properties of the text to be displayed
    m_label1 = new QLabel(this);

    // Display instructions specific to the type of the game
    if(m_type == GameType::SINGLEPLAYER)
    {
        m_label1->setText("<u>INSTRUCTIONS:</u><br><br>Use space bar to flip the gravity");
    }

    else
    {
        m_label1->setText("INSTRUCTIONS:\n\nUse M for flipping gravity of player 1\n Use C for flipping gravity of player 2");
    }

    m_label1->setStyleSheet("font: 20px; color: white");
    m_label1->setAlignment(Qt::AlignCenter);
    m_label1->setGeometry(QRect(QPoint(175, 25), QSize(600, 150)));
    m_label1->show();
    m_label2 = new QLabel(this);

    if(m_type == GameType::SINGLEPLAYER)
    {
        m_label2->setText("<u>RULES</u>:<br><br>1. You should always stay on the track or between<br> "
                          "while flipping but you should not leave the screen<br><br>2. The computer should not catch you<u>");
    }

    else
    {
        m_label2->setText("<u>RULES:</u><br><br>You should always stay on the track or between<br> "
                          "while flipping but you should not leave the screen<br>");
    }

    m_label2->setStyleSheet("font: 20px; color: white");
    m_label2->setAlignment(Qt::AlignCenter);
    m_label2->setGeometry(QRect(QPoint(50, 175), QSize(900, 200)));
    m_label2->show();
}

void InstructionWindow::display()
{
    // Set the position
    this->resize(1000, 500);
    this->move(0, 0);
    //this->setStyleSheet("background-image:url(:/res/objects/acid2.png);");
    QPalette palette;
    palette.setBrush(QPalette::Button,Qt::gray);
    palette.setBrush(QPalette::Background, QBrush(QImage(":/res/objects/bgrocks.png").scaled(1000,500)));
    this->setPalette(palette);
    this->show();
    this->setFixedSize(width(), height());
}

void InstructionWindow::handleEnterGame()
{
    m_enterGame->disconnect();
    // close the instruction window
    this->close();

    // create a new window to select the players
    SelectPlayersWindow* selectPlayersWindow = new SelectPlayersWindow(m_type, this);
    selectPlayersWindow->display();
}
