#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include "BackgroundUpdater.h"
#include "Set1.h"
#include "Set2.h"
#include "BackgroundMusic.h"
#include <QLabel>
#include <QWaitCondition>

Game::Game(GameType type, std::vector <int> playerIDMapping, QWidget* parent): QGraphicsView(parent)
{
    gameType = type;
    isPaused = false;
    isFinished = false;
    playerID = playerIDMapping;

    xShift = 2;
    yShift = 3;

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1000, 500);
    setScene(scene);
    setFixedSize(1000, 500);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Set the alignment to top left corner
    setAlignment(Qt::AlignLeft|Qt::AlignTop);

    // Create a new scoreupdater
    scoreUpdater = new ScoreUpdater;

    // Show score if the game is singleplayer
    if(gameType == GameType::SINGLEPLAYER)
    {
        scene->addItem(scoreUpdater);
        scoreUpdater->setPos(50, 10);
    }

    else
    {
        displayImage = NULL;
    }

    // Store the idle images of both the players
    images[0] = QPixmap(":res/player/" + QString::number(playerID[0]) +"idle1.png");
    images[1] = QPixmap(":res/player/" + QString::number(playerID[1]) +"idle1.png");

    // Set the properties of the pause button
    pauseButton = new QPushButton(this);
    pauseButton->setIcon(QIcon(":/res/objects/pausebutton.png"));
    pauseButton->setIconSize(QSize(50, 50));
    pauseButton->setGeometry(QRect(QPoint(900, 0), QSize(50, 50)));
    connect(pauseButton, SIGNAL(released()), this, SLOT(handlePauseGame()));

    // Pause button is visible by default
    pauseButton->setVisible(true);

    // Set the properties of the resume button
    resumeButton = new QPushButton(this);
    resumeButton->setIcon(QIcon(":/res/objects/playbutton.png"));
    resumeButton->setIconSize(QSize(50, 50));
    resumeButton->setGeometry(QRect(QPoint(900, 0), QSize(50, 50)));
    connect(resumeButton, SIGNAL(released()), this, SLOT(handleResumeGame()));

    // Resume button is invisible by default
    resumeButton->setVisible(false);

    // Register the types which are to be sent/received via signal/slot mechanism
    qRegisterMetaType < Player > ("Player");
    qRegisterMetaType < PlayerState > ("PlayerState");

    // Start background music
    //qWarning() << this->thread()->currentThreadId();

    backgroundMusic = new BackgroundMusic();
    backgroundMusic->moveToThread(backgroundMusic);
    backgroundMusic->start();

    backgroundUpdater = new BackgroundUpdater;
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_P)
    {
       if(!isPaused)
       {
            pauseButton->click();
       }
       else
       {
           resumeButton->click();
       }

       return;
    }

    // DONOT flip the player after the game is finished or paused
    if(isFinished || isPaused)
    {
        event->accept();
        return;
    }

    // The Game Type is Single Player
    if(gameType == GameType::SINGLEPLAYER)
    {
        if(event->key() == Qt::Key_Space)
        {
            // emit signal to worker thread
            emit requestFlipPlayerUpdate(player[0]);
        }

        return;
    }

    // The Game Type is Multi Player
    if(event->key() == Qt::Key_M)
    {
        emit requestFlipPlayerUpdateForPlayer1(player[0]);
    }

    if(event->key() == Qt::Key_C)
    {
        emit requestFlipPlayerUpdateForPlayer2(player[1]);
    }
}

// This function is called when user clicks the X button while the game is running
void Game::closeEvent(QCloseEvent *event)
{
    // Close all running threads
    backgroundMusic->requestInterruption();
/*
    threadForPlayer1->requestInterruption();
    threadForPlayer2->requestInterruption();

    player[0]->runPlayer();
    player[1]->runPlayer();
*/

    /*
     * Set the setAccepted variable to true to
     * indicate that this function wants the event.
     * (Event doesn't propagate to parent widget)
     */

    event->accept();
}

/*
 * In Single Player Game:
 *
 *      player[0] represents the player
 *      player[1] represents the computer
*/

void Game::startSinglePlayerGame()
{
    set1 = new Set1(0);
    set2 = new Set2(set1->endPos);

    for(int i = 0; i < set1->objects.size(); i++)
    {
       scene->addItem(set1->objects[i]);
       set1->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
    }

    for(int i = 0; i < set2->objects.size(); i++)
    {
       scene->addItem(set2->objects[i]);
       set2->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
    }

    // make game focusable
    setFocus();

    player[0] = new Player(0);
    scene->addItem(player[0]);
    player[0]->setPos(200, scene->height() -50 -120 +40);

    player[1] = new Player(1);
    scene->addItem(player[1]);
    player[1]->setPos(50, scene->height() -50 -120 +40);

    threadForPlayer1 = new QThread;
    workerForPlayer1 = new RunPlayerWorker;

    workerForPlayer1->moveToThread(threadForPlayer1);

    QObject::connect(player[0], SIGNAL(requestUpdatePlayerState(Player*,bool,bool,bool,int,int)),
            workerForPlayer1, SLOT(updatePlayerState(Player*,bool,bool,bool,int,int)));

    QObject::connect(workerForPlayer1, SIGNAL(doneUpdating(PlayerState)), player[0],
            SLOT(doneProcessing(PlayerState)));

    QObject::connect(this, SIGNAL(requestFlipPlayerUpdate(Player*)),
                     workerForPlayer1, SLOT(updateFlipPlayerState(Player*)));

    QObject::connect(workerForPlayer1, SIGNAL(doneFlipping(PlayerState)),
                     player[0], SLOT(doneFlipping(PlayerState)));

    threadForPlayer2 = new QThread;
    workerForPlayer2 = new RunPlayerWorker;

    workerForPlayer2->moveToThread(threadForPlayer2);

    QObject::connect(player[1], SIGNAL(requestUpdatePlayerState(Player*,bool,bool,bool,int,int)),
            workerForPlayer2, SLOT(updatePlayerState(Player*,bool,bool,bool,int,int)));

    QObject::connect(workerForPlayer2, SIGNAL(doneUpdating(PlayerState)), player[1],
            SLOT(doneProcessing(PlayerState)));

    threadForPlayer1->start();
    threadForPlayer2->start();

    // add image to show next to the score

    displayImage = new QLabel(this);
    displayImage->setPixmap(images[0].scaled(60, 60,
                                        Qt::KeepAspectRatio, Qt::SmoothTransformation));
    displayImage->setGeometry(QRect(QPoint(0, 0), QSize(60, 60)));
    displayImage->show();

    timer = new QTimer();

    QObject::connect(timer, SIGNAL(timeout()), player[0], SLOT(runPlayer()));
    QObject::connect(timer, SIGNAL(timeout()), player[1], SLOT(runPlayer()));
    QObject::connect(timer, SIGNAL(timeout()), set1, SLOT(updateObjects()));
    QObject::connect(timer, SIGNAL(timeout()), set2, SLOT(updateObjects()));
    QObject::connect(timer, SIGNAL(timeout()), backgroundUpdater, SLOT(update()));
    QObject::connect(timer, SIGNAL(timeout()), scoreUpdater, SLOT(updateScore()));

    timer->start(10);

    // connect scoreUpdater to its timer
    //scoreUpdater->connectStepIncrementTimer();

    //qWarning(":/player/run" + QString::number(2).toLatin1() + ".png");
}

/*
 * In Multiplayer Game:
 *
 *      player[0] represents the 1st player
 *      player[1] represents the 2nd player
*/

void Game::startMultiPlayerGame()
{
    set1 = new Set1(0);
    set2 = new Set2(set1->endPos);

    for(int i = 0; i < set1->objects.size(); i++)
    {
       scene->addItem(set1->objects[i]);
       set1->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
    }

    for(int i = 0; i < set2->objects.size(); i++)
    {
       scene->addItem(set2->objects[i]);
       set2->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
    }

    // make game focusable
    setFocus();

    // add players
    player[0] = new Player(0);
    scene->addItem(player[0]);
    player[0]->setPos(200, scene->height() -50 -120 +40);

    player[1] = new Player(1);
    scene->addItem(player[1]);
    player[1]->setPos(50, scene->height() -50 -120 +40);

    threadForPlayer1 = new QThread;
    workerForPlayer1 = new RunPlayerWorker;

    workerForPlayer1->moveToThread(threadForPlayer1);

    QObject::connect(player[0], SIGNAL(requestUpdatePlayerState(Player*,bool,bool,bool,int,int)),
            workerForPlayer1, SLOT(updatePlayerState(Player*,bool,bool,bool,int,int)));
    QObject::connect(workerForPlayer1, SIGNAL(doneUpdating(PlayerState)), player[0],
            SLOT(doneProcessing(PlayerState)));

    QObject::connect(this, SIGNAL(requestFlipPlayerUpdateForPlayer1(Player*)),
                     workerForPlayer1, SLOT(updateFlipPlayerState(Player*)));
    QObject::connect(workerForPlayer1, SIGNAL(doneFlipping(PlayerState)),
                     player[0], SLOT(doneFlipping(PlayerState)));

    threadForPlayer2 = new QThread;
    workerForPlayer2 = new RunPlayerWorker;

    workerForPlayer2->moveToThread(threadForPlayer2);

    QObject::connect(player[1], SIGNAL(requestUpdatePlayerState(Player*,bool,bool,bool,int,int)),
            workerForPlayer2, SLOT(updatePlayerState(Player*,bool,bool,bool,int,int)));
    QObject::connect(workerForPlayer2, SIGNAL(doneUpdating(PlayerState)), player[1],
            SLOT(doneProcessing(PlayerState)));

    QObject::connect(this, SIGNAL(requestFlipPlayerUpdateForPlayer2(Player*)),
                     workerForPlayer2, SLOT(updateFlipPlayerState(Player*)));
    QObject::connect(workerForPlayer2, SIGNAL(doneFlipping(PlayerState)),
                     player[1], SLOT(doneFlipping(PlayerState)));

    threadForPlayer1->start();
    threadForPlayer2->start();

    timer = new QTimer();

    QObject::connect(timer, SIGNAL(timeout()), player[0], SLOT(runPlayer()));
    QObject::connect(timer, SIGNAL(timeout()), player[1], SLOT(runPlayer()));
    QObject::connect(timer, SIGNAL(timeout()), set1, SLOT(updateObjects()));
    QObject::connect(timer, SIGNAL(timeout()), set2, SLOT(updateObjects()));
    QObject::connect(timer, SIGNAL(timeout()), backgroundUpdater, SLOT(update()));
    QObject::connect(timer, SIGNAL(timeout()), scoreUpdater, SLOT(updateScore()));

    timer->start(10);
    //qWarning(":/player/run" + QString::number(2).toLatin1() + ".png");
}

void Game::reincarnateSet(int idx)
{
    if(idx == 1)
    {
        delete set1;
        qWarning() << "Dead 1";
        set1 = new Set1(set2->objects[0]->rect().x() +set2->endPos);

        for(int i = 0; i < set1->objects.size(); i++)
        {
            scene->addItem(set1->objects[i]);
            set1->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
        }

        QObject::connect(timer, SIGNAL(timeout()), set1, SLOT(updateObjects()));
    }

    else
    {
        delete set2;
        qWarning() << "dead 2";
        set2 = new Set2(set1->objects[0]->rect().x() +set1->endPos);

        for(int i = 0; i < set2->objects.size(); i++)
        {
            scene->addItem(set2->objects[i]);
            set2->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
        }

        QObject::connect(timer, SIGNAL(timeout()), set2, SLOT(updateObjects()));
    }
}

void Game::handlePauseGame()
{
    // hide the pause button
    pauseButton->setVisible(false);

    isPaused = true;

    // set the timer to a large value
    timer->start(10000000);

    // show the resume button
    resumeButton->setVisible(true);
}

void Game::handleResumeGame()
{
    // hide the resume button
    resumeButton->setVisible(false);

    isPaused = false;

    // reset the timer
    timer->start(10);

    // show the pause button
    pauseButton->setVisible(true);
}
