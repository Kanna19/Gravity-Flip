#include "Set2.h"
#include <QList>
#include <QDebug>
#include "Game.h"

extern Game* game;

Set2::Set2(int start_pos)
{
    objects.append(new QGraphicsRectItem(0, 0, 1200, 40));
    objects.last()->setPos(start_pos, 460);

    start_pos += 300;
    objects.append(new QGraphicsRectItem(0, 0, 1200, 140));
    objects.last()->setPos(start_pos, 100);

    start_pos +=100;
    objects.append(new QGraphicsRectItem(0, 0, 40, 40));
    objects.last()->setPos(start_pos, 420);

    start_pos += objects.last()->rect().width() + 100;
    objects.append(new QGraphicsRectItem(0, 0, 40, 40));
    objects.last()->setPos(start_pos, 240);

    start_pos += objects.last()->rect().width() + 100;
    objects.append(new QGraphicsRectItem(0, 0, 40, 40));
    objects.last()->setPos(start_pos, 420);

    start_pos += objects.last()->rect().width() + 100;
    objects.append(new QGraphicsRectItem(0, 0, 40, 40));
    objects.last()->setPos(start_pos, 240);

    endPos = 1500;

    QObject::connect(this,SIGNAL(killMe(int)),game,SLOT(reincarnateSet(int)));

}

void Set2::updateObjects()
{
    //QMutableListIterator<QGraphicsRectItem*> it(objects);
    for(int i = 0; i < objects.size(); i++)
    {
        //qWarning() << "Hello " << objects[i]->x();
        objects[i]->setPos(objects[i]->x() -game->xShift, objects[i]->y());
    }

    if(objects[0]->x() +endPos < 0)
    {
        emit killMe(2);
    }
}
