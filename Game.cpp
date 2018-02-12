#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QObject>
#include <QTimer>

Game::Game()
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    scene->setSceneRect(0,0,800,600);
    setFixedSize(800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsPixmapItem* bottomTiles[10];
    QPixmap tile_image = QPixmap(":res/objects/tile2.png").scaled(80,80);

    for(int i = 0; i < 10; i++)
    {
        bottomTiles[i] = new QGraphicsPixmapItem();
        bottomTiles[i]->setPixmap(tile_image);
        bottomTiles[i]->setPos(i*80,scene->height() - bottomTiles[i]->pixmap().height());
        scene->addItem(bottomTiles[i]);
    }

    QGraphicsPixmapItem* topTiles[10];
    tile_image = tile_image.transformed(QTransform().rotate(180));

    for(int i = 0; i < 10; i++)
    {
        topTiles[i] = new QGraphicsPixmapItem();
        topTiles[i]->setPixmap(tile_image);
        topTiles[i]->setPos(i*80,0);
        scene->addItem(topTiles[i]);
    }

    //create and add player
    player = new Player();
    scene->addItem(player);
    player->setPos(0,scene->height()-80-120+10);

    QTimer* timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(runPlayer()));

    timer->start(50);


    //qWarning(":/player/run" + QString::number(2).toLatin1() + ".png");
}
