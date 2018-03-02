#include "Set1.h"
#include <QList>
#include <QDebug>

Set1::Set1()
{
    int start_pos = 0;

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
}

void Set1::updateObjects()
{
    //QMutableListIterator<QGraphicsRectItem*> it(objects);
    for(int i = 0; i < objects.size(); i++)
    {
        //qWarning() << "Hello " << objects[i]->x();
        objects[i]->setPos(objects[i]->x() -2, objects[i]->y());
        if(objects[i]->x() + objects[i]->rect().width() < 0)
        {
            //qWarning() << "Hello " << objects[i]->x();
            objects[i]->setPos(1000, objects[i]->y());
        }
    }
}
