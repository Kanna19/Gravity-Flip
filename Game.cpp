#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include "ObjectCreator.h"
#include "BackgroundUpdater.h"
#include "Set1.h"
#include "BackgroundMusic.h"
#include "StepSound.h"
#include <QLabel>

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
    }

    // Start step Sound
    stepSound[0] = new StepSound();
    stepSound[0]->moveToThread(stepSound[0]);
    stepSound[0]->start();

    stepSound[1] = new StepSound();
    stepSound[1]->moveToThread(stepSound[1]);
    stepSound[1]->start();

    // Start background music
    qWarning() << this->thread()->currentThreadId();
    backgroundMusic = new BackgroundMusic();
    backgroundMusic->moveToThread(backgroundMusic);
    backgroundMusic->start();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    // The Game Type is Single Player
    if(player_cnt == 1)
    {
        if(event->key() == Qt::Key_Space)
        {
            player[0]->flipPlayer();
        }

        return;
    }

    // The Game Type is Multi Player
    if(event->key() == Qt::Key_C)
    {
       player[0]->flipPlayer();
    }

    if(event->key() == Qt::Key_M)
    {
        player[1]->flipPlayer();
    }
}

/*
 * In Single Player Game:
 *
 *      player[0] represents the player
*/

void Game::startSinglePlayerGame()
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

    // player

    player[0] = new Player(1);
    scene->addItem(player[0]);
    player[0]->setPos(200, scene->height() -50 -120 +40);

    player[1] = new Player(2);
    scene->addItem(player[1]);
    player[1]->setPos(100, scene->height() -50 -120 +40);

    QPixmap image(":res/player/" + QString::number(playerID[1]) +"idle1.png");

    QLabel* displayImage = new QLabel(this);
    displayImage->setPixmap(image.scaled(60, 60,
                                        Qt::KeepAspectRatio, Qt::SmoothTransformation));
    displayImage->setGeometry(QRect(QPoint(0, 0), QSize(60, 60)));
    displayImage->show();

    QTimer* timer = new QTimer();

    QObject::connect(timer, SIGNAL(timeout()), player[0], SLOT(runPlayer()));
    QObject::connect(timer, SIGNAL(timeout()), set, SLOT(updateObjects()));
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

    // player 1
    player[0] = new Player(1);
    scene->addItem(player[0]);
    player[0]->setPos(100, scene->height() -50 -120 +40);

    // player 2
    player[1] = new Player(2);
    scene->addItem(player[1]);
    player[1]->setPos(200, scene->height() -50 -120 +40);

    QTimer* timer = new QTimer();

    QObject::connect(timer, SIGNAL(timeout()), player[0], SLOT(runPlayer()));
    QObject::connect(timer, SIGNAL(timeout()), player[1], SLOT(runPlayer()));
    QObject::connect(timer, SIGNAL(timeout()), set, SLOT(updateObjects()));
    QObject::connect(timer, SIGNAL(timeout()), backgroundUpdater, SLOT(update()));

    timer->start(10);
    //qWarning(":/player/run" + QString::number(2).toLatin1() + ".png");
}
