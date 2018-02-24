#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include "ObjectCreator.h"
#include "BackgroundUpdater.h"
#include "Set1.h"

Game::Game(QWidget* parent): QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    scene->setSceneRect(0, 0, 1000, 500);
    setFixedSize(1000, 500);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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

    // player 1
    player1 = new Player(1);
    scene->addItem(player1);
    player1->setPos(100, scene->height() -50 -120 +40);

    // player 2
    player2 = new Player(2);
    scene->addItem(player2);
    player2->setPos(200, scene->height() -50 -120 +40);

    QTimer* timer = new QTimer();

    QObject::connect(timer,SIGNAL(timeout()),player1,SLOT(runPlayer()));
    QObject::connect(timer,SIGNAL(timeout()),player2,SLOT(runPlayer()));
    QObject::connect(timer,SIGNAL(timeout()),set,SLOT(updateObjects()));
    QObject::connect(timer,SIGNAL(timeout()),backgroundUpdater,SLOT(update()));

    timer->start(10);

    //qWarning(":/player/run" + QString::number(2).toLatin1() + ".png");
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_C)
    {
       player1->flipPlayer();
    }

    if(event->key() == Qt::Key_M)
    {
        player2->flipPlayer();
    }
}
