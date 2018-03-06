#include "InstructionWindow.h"
#include "MainWindow.h"
#include "GameType.h"
#include "BackgroundMusic.h"
#include <QLabel>
#include <QVBoxLayout>

BackgroundMusic* musicPlayer;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    musicPlayer = new BackgroundMusic(0);
    musicPlayer->moveToThread(musicPlayer);
    musicPlayer->start();

    QLabel* mainTitle = new QLabel("Gravity Flip");
    QFont f("Arial", 32, QFont::Bold);
    mainTitle->setStyleSheet("QLabel {color : white; alignment : center}");
    mainTitle->setFont(f);

    QWidget* wid = new QWidget(this);
    this->setCentralWidget(wid);
    QVBoxLayout* layout = new QVBoxLayout();

    // create the required buttons and set their parent to "this"
    m_singlePlayer = new CustomButton("Single Player");
    m_multiPlayer = new CustomButton("Multi Player");
    m_exitGame = new CustomButton("Exit");

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
    connect(m_singlePlayer,SIGNAL(pressed()),m_singlePlayer,SLOT(changeColor()));
    connect(m_multiPlayer,SIGNAL(pressed()),this,SLOT(changeColor()));
    connect(m_exitGame,SIGNAL(pressed()),this,SLOT(changeColor()));
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
    // Disconnect all button signals
    m_singlePlayer->disconnect();
    m_multiPlayer->disconnect();
    m_exitGame->disconnect();

    // close the main window
    this->close();

    // create a new window for instructions
    InstructionWindow *instructionWindow = new InstructionWindow(GameType::SINGLEPLAYER, this);
    instructionWindow->display();
}

void MainWindow::handleMultiPlayer()
{
    // Disconnect all button signals
    m_singlePlayer->disconnect();
    m_multiPlayer->disconnect();
    m_exitGame->disconnect();

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

void MainWindow::changeColor()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    QPalette p = pButton->palette();
    p.setColor(QPalette::Button, Qt::yellow);
    pButton->setPalette(p);
}
