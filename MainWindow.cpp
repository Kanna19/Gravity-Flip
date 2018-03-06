#include "InstructionWindow.h"
#include "MainWindow.h"
#include "GameType.h"
#include "BackgroundMusic.h"
#include <QLabel>
#include <QVBoxLayout>

BackgroundMusic* musicPlayer;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    // Initialize music player
    musicPlayer = new BackgroundMusic(0);
    musicPlayer->moveToThread(musicPlayer);
    musicPlayer->start();

    // Add title
    QLabel* mainTitle = new QLabel("Gravity Flip", this);
    QFont f("Arial", 32, QFont::Bold);
    mainTitle->setStyleSheet("QLabel {color : white;}");
    mainTitle->setFont(f);
    mainTitle->setGeometry(380, 50, 350, 50);

    // Widget to add buttons
    QWidget* wid = new QWidget(this);

    // Set wid as the central widget of MainWindow
    this->setCentralWidget(wid);

    // Create a vertical layout for buttons
    QVBoxLayout* layout = new QVBoxLayout();

    // Create the required buttons
    m_singlePlayer = new CustomButton("Single Player");
    m_multiPlayer = new CustomButton("Multi Player");
    m_exitGame = new CustomButton("Exit");

    // Add buttons to layout
    layout->addWidget(m_singlePlayer);
    layout->addWidget(m_multiPlayer);
    layout->addWidget(m_exitGame);

    // Set alignment and spacing of layout
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(50);

    // Set size of buttons
    m_singlePlayer->setFixedSize(QSize(200,50));
    m_multiPlayer->setFixedSize(QSize(200,50));
    m_exitGame->setFixedSize(QSize(200,50));

    // Set the layout of the central widget
    wid->setLayout(layout);

    // Connect the buttons to the appropriate slots
    connect(m_singlePlayer,SIGNAL(pressed()),m_singlePlayer,SLOT(changeColor()));
    connect(m_multiPlayer,SIGNAL(pressed()),m_multiPlayer,SLOT(changeColor()));
    connect(m_exitGame,SIGNAL(pressed()),m_exitGame,SLOT(changeColor()));
    connect(m_singlePlayer, SIGNAL(released()), this, SLOT(handleSinglePlayer()));
    connect(m_multiPlayer, SIGNAL(released()), this, SLOT(handleMultiPlayer()));
    connect(m_exitGame, SIGNAL(released()), this, SLOT(handleExitGame()));
}

void MainWindow::display()
{
    // Set palette of MainWindow
    QPalette palette;
    palette.setBrush(QPalette::Button,Qt::gray);
    palette.setBrush(QPalette::Background, QBrush(QImage(":/res/objects/bgrocks.png").scaled(1000,500)));
    this->setPalette(palette);

    // Resize and show MainWindow
    this->resize(1000, 500);
    this->setFixedSize(width(), height());
    this->move(0, 0);
    this->show();
}

void MainWindow::handleSinglePlayer()
{
    // Disconnect all button signals
    m_singlePlayer->disconnect();
    m_multiPlayer->disconnect();
    m_exitGame->disconnect();

    // Close the main window
    this->close();

    // Create a new window for instructions
    InstructionWindow *instructionWindow = new InstructionWindow(GameType::SINGLEPLAYER, this);
    instructionWindow->display();
}

void MainWindow::handleMultiPlayer()
{
    // Disconnect all button signals
    m_singlePlayer->disconnect();
    m_multiPlayer->disconnect();
    m_exitGame->disconnect();

    // Close the main window
    this->close();

    // Create a new window for instructions
    InstructionWindow *instructionWindow = new InstructionWindow(GameType::MULTIPLAYER, this);
    instructionWindow->display();
}

void MainWindow::handleExitGame()
{
    // Close the main window
    this->close();
}
