#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include "ObjectCreator.h"
#include "BackgroundUpdater.h"

Game::Game(QWidget* parent): QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    scene->setSceneRect(0,0,1000,400);
    setFixedSize(1000,400);
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

    //call Object Creator
    ObjectCreator* objectCreator = new ObjectCreator();
    QTimer* objectTimer = new QTimer();
    QObject::connect(objectTimer,SIGNAL(timeout()),objectCreator,SLOT(createObject()));

    objectTimer->start(1000);

    //create backgroundUpdater
    BackgroundUpdater* backgroundUpadter = new BackgroundUpdater;

    //create and add player
    player = new Player();
    scene->addItem(player);
    player->setPos(300,scene->height()-50-120+10);

    //make player focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    QTimer* timer = new QTimer();


    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(runPlayer()));
    QObject::connect(timer,SIGNAL(timeout()),objectCreator,SLOT(updateObjects()));
    QObject::connect(timer,SIGNAL(timeout()),backgroundUpadter,SLOT(update()));

    timer->start(10);


    //qWarning(":/player/run" + QString::number(2).toLatin1() + ".png");
}
