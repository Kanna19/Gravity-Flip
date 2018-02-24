#ifndef SET1_H
#define SET1_H

#include <QGraphicsRectItem>
#include <QObject>

class Set1: public QObject
{
Q_OBJECT

public:

    // member functions

    Set1();

    // member variables

    QList<QGraphicsRectItem*> objects;

public slots:

    void updateObjects();
};

#endif // SET1_H
