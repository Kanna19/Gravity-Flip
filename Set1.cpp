#include "Set1.h"
#include <QList>
#include <QDebug>
#include "Game.h"

extern Game* game;

Set1::Set1(int start_pos)
{
    objects.append(new QGraphicsRectItem(0, 0, 600, 40));
    objects.last()->setPos(start_pos, 460);

    start_pos += 400;
    objects.append(new QGraphicsRectItem(0, 0, 300, 140));
    objects.last()->setPos(start_pos, 100);

    start_pos += objects.last()->rect().width() + 50;
    objects.append(new QGraphicsRectItem(0, 0, 200, 40));
    objects.last()->setPos(start_pos, 460);

    start_pos += objects.last()->rect().width() + 50;
    objects.append(new QGraphicsRectItem(0, 0, 200, 40));
    objects.last()->setPos(start_pos, 160);

    start_pos += objects.last()->rect().width() + 50;
    objects.append(new QGraphicsRectItem(0, 0, 200, 40));
    objects.last()->setPos(start_pos, 460);

    start_pos += objects.last()->rect().width() + 50;
    objects.append(new QGraphicsRectItem(0, 0, 200, 40));
    objects.last()->setPos(start_pos, 160);

    start_pos += objects.last()->rect().width() + 50;
    objects.append(new QGraphicsRectItem(0, 0, 200, 40));
    objects.last()->setPos(start_pos, 460);

    endPos = 1900;

    QObject::connect(this,SIGNAL(killMe(int)),game,SLOT(reincarnateSet(int)));
}

void Set1::updateObjects()
{    
    for(int i = 0; i < objects.size(); i++)
    {
        //qWarning() << "Hello " << objects[i]->x();
        objects[i]->setPos(objects[i]->x() -game->xShift, objects[i]->y());
    }

    if(objects.last()->x()+objects.last()->rect().width() < 0)
    {
        emit killMe(1);
    }
}
