#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include "ObjectCreator.h"
#include "BackgroundUpdater.h"
#include "Set1.h"
#include "Set2.h"
#include "BackgroundMusic.h"
#include <QLabel>
#include <QWaitCondition>

Game::Game(int cnt, std::vector <int> playerIDMapping, QWidget* parent): QGraphicsView(parent)
{
    player_cnt = cnt;
    isFinished = false;
    playerID = playerIDMapping;

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1000, 500);
    setScene(scene);
    setFixedSize(1000, 500);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Show score if the game is single player
    if(player_cnt == 1)
    {
        scoreUpdater = new ScoreUpdater;
        scene->addItem(scoreUpdater);
        scoreUpdater->setPos(50, 10);
    }

    else
    {
        scoreUpdater = NULL;
        displayImage = NULL;
    }

    // Store the idle images of both the players
    images[0] = QPixmap(":res/player/" + QString::number(playerID[0]) +"idle1.png");
    images[1] = QPixmap(":res/player/" + QString::number(playerID[1]) +"idle1.png");


    qRegisterMetaType < Player > ("Player");
    qRegisterMetaType < PlayerState > ("PlayerState");

    // Start background music
    qWarning() << this->thread()->currentThreadId();
    backgroundMusic = new BackgroundMusic();
    backgroundMusic->moveToThread(backgroundMusic);
    backgroundMusic->start();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    // DONOT flip the player after the game is finished
    if(isFinished)
    {
        event->accept();
        return;
    }

    // The Game Type is Single Player
    if(player_cnt == 1)
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
    set[0] = new Set2(0);
    set[1] = new Set2(1500);

    for(int i = 0; i < set[0]->objects.size(); i++)
    {
       scene->addItem(set[0]->objects[i]);
       set[0]->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
    }

    for(int i = 0; i < set[1]->objects.size(); i++)
    {
       scene->addItem(set[1]->objects[i]);
       set[1]->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
    }

    // create backgroundUpdater
    BackgroundUpdater* backgroundUpdater = new BackgroundUpdater;

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

    QObject::connect(player[0], SIGNAL(requestUpdatePlayerState(Player*,bool,bool,bool)),
            workerForPlayer1, SLOT(updatePlayerState(Player*,bool,bool,bool)));

    QObject::connect(workerForPlayer1, SIGNAL(doneUpdating(PlayerState)), player[0],
            SLOT(doneProcessing(PlayerState)));

    QObject::connect(this, SIGNAL(requestFlipPlayerUpdate(Player*)),
                     workerForPlayer1, SLOT(updateFlipPlayerState(Player*)));

    QObject::connect(workerForPlayer1, SIGNAL(doneFlipping(PlayerState)),
                     player[0], SLOT(doneFlipping(PlayerState)));

    threadForPlayer2 = new QThread;
    workerForPlayer2 = new RunPlayerWorker;

    workerForPlayer2->moveToThread(threadForPlayer2);

    QObject::connect(player[1], SIGNAL(requestUpdatePlayerState(Player*,bool,bool,bool)),
            workerForPlayer2, SLOT(updatePlayerState(Player*,bool,bool,bool)));

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
    QObject::connect(timer, SIGNAL(timeout()), set[0], SLOT(updateObjects()));
    QObject::connect(timer, SIGNAL(timeout()), set[1], SLOT(updateObjects()));
    QObject::connect(timer, SIGNAL(timeout()), backgroundUpdater, SLOT(update()));
    QObject::connect(timer, SIGNAL(timeout()), scoreUpdater, SLOT(updateScore()));

    timer->start(10);

    // connect scoreUpdater to its timer
    scoreUpdater->connectStepIncrementTimer();

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
    Set1* set = new Set1();

    for(int i = 0; i < set->objects.size(); i++)
    {
       scene->addItem(set->objects[i]);
       set->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
    }

    // create backgroundUpdater
    BackgroundUpdater* backgroundUpdater = new BackgroundUpdater;

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

    QObject::connect(player[0], SIGNAL(requestUpdatePlayerState(Player*,bool,bool,bool)),
            workerForPlayer1, SLOT(updatePlayerState(Player*,bool,bool,bool)));
    QObject::connect(workerForPlayer1, SIGNAL(doneUpdating(PlayerState)), player[0],
            SLOT(doneProcessing(PlayerState)));

    QObject::connect(this, SIGNAL(requestFlipPlayerUpdateForPlayer1(Player*)),
                     workerForPlayer1, SLOT(updateFlipPlayerState(Player*)));
    QObject::connect(workerForPlayer1, SIGNAL(doneFlipping(PlayerState)),
                     player[0], SLOT(doneFlipping(PlayerState)));

    threadForPlayer2 = new QThread;
    workerForPlayer2 = new RunPlayerWorker;

    workerForPlayer2->moveToThread(threadForPlayer2);

    QObject::connect(player[1], SIGNAL(requestUpdatePlayerState(Player*,bool,bool,bool)),
            workerForPlayer2, SLOT(updatePlayerState(Player*,bool,bool,bool)));
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
    QObject::connect(timer, SIGNAL(timeout()), set, SLOT(updateObjects()));
    QObject::connect(timer, SIGNAL(timeout()), backgroundUpdater, SLOT(update()));

    timer->start(10);
    //qWarning(":/player/run" + QString::number(2).toLatin1() + ".png");
}

void Game::reincarnateSet(int idx)
{
    int nextIdx = (idx +1) % 2;
    qWarning() << "I am dead";
    delete set[idx];
    set[idx] = new Set2(set[nextIdx]->objects[0]->rect().x()+1500);

    for(int i = 0; i < set[idx]->objects.size(); i++)
    {
       scene->addItem(set[idx]->objects[i]);
       set[idx]->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
    }

    QObject::connect(timer, SIGNAL(timeout()), set[idx], SLOT(updateObjects()));
}
