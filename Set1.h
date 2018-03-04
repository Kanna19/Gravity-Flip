#ifndef SET1_H
#define SET1_H

#include <QGraphicsRectItem>
#include <QObject>

class Set1: public QObject
{
Q_OBJECT

public:

    // member functions

    Set1(int);

    // member variables

    QList<QGraphicsRectItem*> objects;
    int endPos;

public slots:

    void updateObjects();

signals:

    void killMe(int);
};

#endif // SET1_H
