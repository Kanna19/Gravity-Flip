#include "ObjectCreator.h"
#include "Obstacle.h"
#include "Game.h"
#include <stdlib.h>
#include <QVector>

extern Game* game;

ObjectCreator::ObjectCreator()
{

}

void ObjectCreator::createObject()
{
    Obstacle* obstacle = new Obstacle();
    game->scene->addItem(obstacle);
    objectsList.append(obstacle);

    srand(time(NULL));

    int yPos = rand()%250;
    yPos += 50;
    obstacle->setPos(game->scene->width() - obstacle->rect().width(), yPos);
}

void ObjectCreator::updateObjects()
{
    QList<Obstacle*>::iterator it = objectsList.begin();
    while(it != objectsList.end())
    {
        (*it)->setPos((*it)->x()-2, (*it)->y());
        if((*it)->x() + 300 < 0)
        {
            objectsList.erase(it);
            delete (*it);
        }

        it++;
    }
}
