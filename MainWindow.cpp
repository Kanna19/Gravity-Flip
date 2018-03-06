#include "InstructionWindow.h"
#include "MainWindow.h"
#include "GameType.h"
#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    QLabel* mainTitle = new QLabel("Gravity Flip");
    QFont f("Arial", 32, QFont::Bold);
    mainTitle->setStyleSheet("QLabel {color : white; alignment : center}");
    mainTitle->setFont(f);

    QWidget* wid = new QWidget(this);
    this->setCentralWidget(wid);
    QVBoxLayout* layout = new QVBoxLayout();

    // create the required buttons and set their parent to "this"
    m_singlePlayer = new QPushButton("Single Player");
    m_multiPlayer = new QPushButton("Multi Player");
    m_exitGame = new QPushButton("Exit");

    // set the size and position of the buttons
    /*m_singlePlayer->setGeometry(QRect(QPoint(350, 100), QSize(200, 50)));
    m_multiPlayer->setGeometry(QRect(QPoint(350, 200), QSize(200, 50)));
    m_exitGame->setGeometry(QRect(QPoint(350, 300), QSize(200, 50)));*/

    layout->addWidget(mainTitle);
    layout->addWidget(m_singlePlayer);
    layout->addWidget(m_multiPlayer);
    layout->addWidget(m_exitGame);

    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(50);

    m_singlePlayer->setFixedSize(QSize(200,50));
    m_multiPlayer->setFixedSize(QSize(200,50));
    m_exitGame->setFixedSize(QSize(200,50));


    wid->setLayout(layout);

    // connect the buttons to the appropriate slots
    connect(m_singlePlayer, SIGNAL(released()), this, SLOT(handleSinglePlayer()));
    connect(m_multiPlayer, SIGNAL(released()), this, SLOT(handleMultiPlayer()));
    connect(m_exitGame, SIGNAL(released()), this, SLOT(handleExitGame()));
}

void MainWindow::display()
{
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

void MainWindow::handleSinglePlayer()
{
    // close the main window
    this->close();

    // create a new window for instructions
    InstructionWindow *instructionWindow = new InstructionWindow(GameType::SINGLEPLAYER, this);
    instructionWindow->display();
}

void MainWindow::handleMultiPlayer()
{
    // close the main window
    this->close();

    // create a new window for instructions
    InstructionWindow *instructionWindow = new InstructionWindow(GameType::MULTIPLAYER, this);
    instructionWindow->display();
}

void MainWindow::handleExitGame()
{
    // close the main window
    this->close();
}
