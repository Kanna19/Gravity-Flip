#include "Set1.h"
#include "Game.h"

extern Game* game;

Set1::Set1(int startPos)
{
    // Create objects of set
    objects.append(new QGraphicsRectItem(0, 0, 600, 40));
    objects.last()->setPos(startPos, 460);

    startPos += 400;
    objects.append(new QGraphicsRectItem(0, 0, 300, 140));
    objects.last()->setPos(startPos, 100);

    startPos += objects.last()->rect().width() + 50;
    objects.append(new QGraphicsRectItem(0, 0, 200, 40));
    objects.last()->setPos(startPos, 460);

    startPos += objects.last()->rect().width() + 50;
    objects.append(new QGraphicsRectItem(0, 0, 200, 40));
    objects.last()->setPos(startPos, 160);

    startPos += objects.last()->rect().width() + 50;
    objects.append(new QGraphicsRectItem(0, 0, 200, 40));
    objects.last()->setPos(startPos, 460);

    startPos += objects.last()->rect().width() + 50;
    objects.append(new QGraphicsRectItem(0, 0, 200, 40));
    objects.last()->setPos(startPos, 160);

    startPos += objects.last()->rect().width() + 50;
    objects.append(new QGraphicsRectItem(0, 0, 200, 40));
    objects.last()->setPos(startPos, 460);

    // Total length of set
    endPos = 1900;

    // Connect killMe signal to reincarnateSet slot
    QObject::connect(this,SIGNAL(killMe(int)),game,SLOT(reincarnateSet(int)));
}

void Set1::updateObjects()
{
    // Change position of all objects in set
    for(int i = 0; i < objects.size(); i++)
    {
        objects[i]->setPos(objects[i]->x() -game->xShift, objects[i]->y());
    }

    // Send signal to kill this set
    if(objects[0]->x() +endPos < 0)
    {
        emit killMe(1);
    }
}
