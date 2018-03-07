#include "Set2.h"
#include "Game.h"

extern Game* game;

Set2::Set2(int startPos)
{
    // Create objects of set
    objects.append(new QGraphicsRectItem(0, 0, 1200, 40));
    objects.last()->setPos(startPos, 460);

    startPos += 300;
    objects.append(new QGraphicsRectItem(0, 0, 1200, 140));
    objects.last()->setPos(startPos, 100);

    startPos +=100;
    objects.append(new QGraphicsRectItem(0, 0, 40, 40));
    objects.last()->setPos(startPos, 420);

    startPos += objects.last()->rect().width() + 100;
    objects.append(new QGraphicsRectItem(0, 0, 40, 40));
    objects.last()->setPos(startPos, 240);

    startPos += objects.last()->rect().width() + 100;
    objects.append(new QGraphicsRectItem(0, 0, 40, 40));
    objects.last()->setPos(startPos, 420);

    startPos += objects.last()->rect().width() + 100;
    objects.append(new QGraphicsRectItem(0, 0, 40, 40));
    objects.last()->setPos(startPos, 240);

    // Total length of set
    endPos = 1500;

    // Connect killMe signal to reincarnateSet slot
    QObject::connect(this,SIGNAL(killMe(int)),game,SLOT(reincarnateSet(int)));

}

void Set2::updateObjects()
{
    // Change position of all objects in set
    for(int i = 0; i < objects.size(); i++)
    {
        objects[i]->setPos(objects[i]->x() -game->xShift, objects[i]->y());
    }

    // Send signal to kill this set
    if(objects[0]->x() +endPos < 0)
    {
        emit killMe(2);
    }
}
