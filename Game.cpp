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
    scene->setSceneRect(0,0,1000,500);
    setFixedSize(1000,500);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /*QGraphicsPixmapItem* bottomTiles[20];
    QPixmap tile_image = QPixmap(":res/objects/tile2.png").scaled(50,50);

    for(int i = 0; i < 20; i++)
    {
        bottomTiles[i] = new QGraphicsPixmapItem();
        bottomTiles[i]->setPixmap(tile_image);
        bottomTiles[i]->setPos(i*50,scene->height() - bottomTiles[i]->pixmap().height());
        scene->addItem(bottomTiles[i]);
    }

    QGraphicsPixmapItem* topTiles[20];
    tile_image = tile_image.transformed(QTransform().rotate(180));

    for(int i = 0; i < 20; i++)
    {
        topTiles[i] = new QGraphicsPixmapItem();
        topTiles[i]->setPixmap(tile_image);
        topTiles[i]->setPos(i*50,0);
        scene->addItem(topTiles[i]);
    }*/

    /*call Object Creator
    ObjectCreator* objectCreator = new ObjectCreator();
    QTimer* objectTimer = new QTimer();
    objectCreator->createObject();*/

    Set1* set = new Set1();

    for(int i=0; i<set->objects.size(); i++)
    {
       scene->addItem(set->objects[i]);
       set->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40,40)));
    }

    //QObject::connect(objectTimer,SIGNAL(timeout()),objectCreator,SLOT(createObject()));

    //objectTimer->start(1000);

    //create backgroundUpdater
    BackgroundUpdater* backgroundUpadter = new BackgroundUpdater;

    //make game focusable
    setFocus();

    //create and add player
    player1 = new Player(1);
    scene->addItem(player1);
    player1->setPos(300,scene->height()-50-120+40);

    //player 2
    player2 = new Player(2);
    scene->addItem(player2);
    player2->setPos(400,scene->height()-50-120+40);


    QTimer* timer = new QTimer();


    QObject::connect(timer,SIGNAL(timeout()),player1,SLOT(runPlayer()));
    QObject::connect(timer,SIGNAL(timeout()),player2,SLOT(runPlayer()));
    QObject::connect(timer,SIGNAL(timeout()),set,SLOT(updateObjects()));
    QObject::connect(timer,SIGNAL(timeout()),backgroundUpadter,SLOT(update()));

    timer->start(10);


    //qWarning(":/player/run" + QString::number(2).toLatin1() + ".png");
}

void Game::keyPressEvent(QKeyEvent *event)
{
   if(event->key() == Qt::Key_C) player1->flipPlayer();
   if(event->key() == Qt::Key_M) player2->flipPlayer();
}

