#include "InstructionWindow.h"
#include "SelectPlayersWindow.h"
#include <QLabel>
#include <QPixmap>
#include <QDebug>

InstructionWindow::InstructionWindow(int cnt, QWidget *parent):
    QMainWindow(parent)
{
    // create the required buttons and set their parent to "this"
    m_enterGame = new QPushButton("Enter", this);

    // set the size and position of the buttons

    m_enterGame->setGeometry(QRect(QPoint(400, 400), QSize(200, 50)));

    // connect the buttons to the appropriate slots

    connect(m_enterGame, SIGNAL(released()), this, SLOT(handleEnterGame()));
    m_cnt = cnt;

    // Set the desired properties of the text to be displayed
    m_label1 = new QLabel(this);

    if(cnt == 1)
    {
        m_label1->setText("INSTRUCTIONS:\n\nUSE SPACE BAR TO FLIP THE GRAVITY");
    }

    else
    {
        m_label1->setText("INSTRUCTIONS:\n\nUSE M FOR FLIPPING GRAVITY OF PLAYER 1\n USE C FOR FLIPPING GRAVITY OF PLAYER 2");
    }

    m_label1->setStyleSheet("font: 25px; color: blue");
    m_label1->setAlignment(Qt::AlignCenter);
    m_label1->setGeometry(QRect(QPoint(175, 25), QSize(600, 150)));
    m_label1->show();
    m_label2 = new QLabel(this);

    if(cnt==1)
    {
        m_label2->setText("RULES:\n\n1. YOU SHOULD ALWAYS STAY ON THE TRACK OR BETWEEN\n "
                          "WHILE FLIPPING BUT YOU SHOULD NOT LEAVE THE SCREEN\n\n2. THE COMPUTER SHOULD NOT CATCH YOU\n");
    }
    else
    {
        m_label2->setText("RULES:\n\n1. YOU SHOULD ALWAYS STAY ON THE TRACK OR BETWEEN\n "
                          "WHILE FLIPPING BUT YOU SHOULD NOT LEAVE THE SCREEN\n");
    }

    m_label2->setStyleSheet("font: 25px; color: blue");
    m_label2->setAlignment(Qt::AlignCenter);
    m_label2->setGeometry(QRect(QPoint(50, 175), QSize(900, 200)));
    m_label2->show();
}

void InstructionWindow::display()
{
    // Set the position
    this->resize(1000, 500);
    this->move(0, 0);
    this->setStyleSheet("background-image:url(:/res/objects/acid2.png);");
    this->show();
}

void InstructionWindow::handleEnterGame()
{
    if(m_cnt == 1)
    {
        // close the main window
        this->close();

        // create a new window to select the players
        SelectPlayersWindow *selectPlayersWindow = new SelectPlayersWindow(1, this);
        selectPlayersWindow->display();
    }
    else
    {
        // close the main window
        this->close();

        // create a new window to select the players
        SelectPlayersWindow *selectPlayersWindow = new SelectPlayersWindow(2, this);
        selectPlayersWindow->display();
    }
}
