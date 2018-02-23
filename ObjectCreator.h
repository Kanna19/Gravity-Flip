#ifndef OBJECTCREATOR_H
#define OBJECTCREATOR_H

#include <QObject>
#include <QList>
#include "Obstacle.h"
#include "Set1.h"

class ObjectCreator: public QObject
{
Q_OBJECT
public:
    ObjectCreator();

    QList<Obstacle*> objectsList;
    Set1* set;

public slots:
    void createObject();
    void updateObjects();
};

#endif // OBJECTCREATOR_H
