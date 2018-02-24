#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include "ObjectCreator.h"
#include "BackgroundUpdater.h"
#include "Set1.h"

Game::Game(int cnt, QWidget* parent): QGraphicsView(parent)
{
    player_cnt = cnt;

    scene = new QGraphicsScene(this);
    setScene(scene);
    scene->setSceneRect(0, 0, 1000, 500);
    setFixedSize(1000, 500);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Start single or multiplayer game depending on the input

    if(player_cnt == 1)
    {
        startSinglePlayerGame();
    }

    else
    {
        startMultiPlayerGame();
    }
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
    player.resize(1);
    player[0] = new Player(1);
    scene->addItem(player[0]);
    player[0]->setPos(100, scene->height() -50 -120 +40);

    QTimer* timer = new QTimer();

    QObject::connect(timer,SIGNAL(timeout()),player[0],SLOT(runPlayer()));
    QObject::connect(timer,SIGNAL(timeout()),set,SLOT(updateObjects()));
    QObject::connect(timer,SIGNAL(timeout()),backgroundUpdater,SLOT(update()));

    timer->start(10);

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

    player.resize(2);

    // player 1
    player[0] = new Player(1);
    scene->addItem(player[0]);
    player[0]->setPos(100, scene->height() -50 -120 +40);

    // player 2
    player[1] = new Player(2);
    scene->addItem(player[1]);
    player[1]->setPos(200, scene->height() -50 -120 +40);

    QTimer* timer = new QTimer();

    QObject::connect(timer,SIGNAL(timeout()),player[0],SLOT(runPlayer()));
    QObject::connect(timer,SIGNAL(timeout()),player[1],SLOT(runPlayer()));
    QObject::connect(timer,SIGNAL(timeout()),set,SLOT(updateObjects()));
    QObject::connect(timer,SIGNAL(timeout()),backgroundUpdater,SLOT(update()));

    timer->start(10);

    //qWarning(":/player/run" + QString::number(2).toLatin1() + ".png");
}
