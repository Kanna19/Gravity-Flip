#ifndef OBJECTCREATOR_H
#define OBJECTCREATOR_H

#include <QObject>
#include <QList>
#include "Obstacle.h"

class ObjectCreator: public QObject
{
Q_OBJECT
public:
    ObjectCreator();

    QList<Obstacle*> objectsList;

public slots:
    void createObject();
    void updateObjects();
};

#endif // OBJECTCREATOR_H
