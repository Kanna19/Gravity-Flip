#include "NoobSet.h"
#include "Game.h"

extern Game* game;

NoobSet::NoobSet(int start_pos)
{
    // Create objects of set
    objects.append(new QGraphicsRectItem(0, 0, 1400, 40));
    objects.last()->setPos(start_pos, 460);

    objects.append(new QGraphicsRectItem(0, 0, 1550, 40));
    objects.last()->setPos(start_pos, 160);

    start_pos += 500;
    objects.append(new QGraphicsRectItem(0, 0, 40, 40));
    objects.last()->setPos(start_pos, 420);

    start_pos += 500;
    objects.append(new QGraphicsRectItem(0, 0, 40, 40));
    objects.last()->setPos(start_pos, 200);

    // Total length of set
    endPos = 1550;

    // Connect killMe signal to reincarnateSet slot
    QObject::connect(this,SIGNAL(killMe(int)),game,SLOT(reincarnateSet(int)));
}

void NoobSet::updateObjects()
{
    // Change position of all objects in set
    for(int i = 0; i < objects.size(); i++)
    {
        objects[i]->setPos(objects[i]->x() -game->xShift, objects[i]->y());
    }

    // Send signal to kill this set
    if(objects[1]->x() +endPos < 0)
    {
        emit killMe(0);
    }
}
