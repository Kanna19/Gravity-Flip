#ifndef OBJECTCREATOR_H
#define OBJECTCREATOR_H

#include <QObject>
#include <QList>
#include "Set1.h"

class ObjectCreator: public QObject
{
Q_OBJECT

public:

    // member functions
    ObjectCreator();

    // member variables
    Set1* set;

public slots:

    void createObject();
    void updateObjects();
};

#endif // OBJECTCREATOR_H
