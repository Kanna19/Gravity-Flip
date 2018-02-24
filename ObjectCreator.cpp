#include "ObjectCreator.h"
#include "Game.h"
#include "Set1.h"
#include <stdlib.h>
#include <QVector>
#include <ObjectCreator.h>
#include <QMutableListIterator>

extern Game* game;

ObjectCreator::ObjectCreator()
{
    set = NULL;
}

void ObjectCreator::createObject()
{
    set = new Set1();
}

void ObjectCreator::updateObjects()
{
    QMutableListIterator<QGraphicsRectItem*> it(set->objects);
    while(it.hasNext())
    {
        it.peekNext()->setPos(it.peekNext()->x() -2, it.peekNext()->y());
        if(it.peekNext()->x() + it.peekNext()->rect().width() < 0)
        {
            it.peekNext()->setPos(1000, it.peekNext()->y());
            it.next();
        }
    }
}
