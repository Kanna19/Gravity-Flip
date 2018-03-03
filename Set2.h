#ifndef SET2_H
#define SET2_H

#include <QGraphicsRectItem>
#include <QObject>

class Set2: public QObject
{
Q_OBJECT

public:

    // member functions

    Set2(int);

    // member variables

    QList<QGraphicsRectItem*> objects;
    int endPos;

public slots:

    void updateObjects();

signals:

    void killMe(int);
};

#endif // SET2_H
