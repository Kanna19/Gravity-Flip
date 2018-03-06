#ifndef NOOBSET_H
#define NOOBSET_H

#include <QGraphicsRectItem>
#include <QObject>

class NoobSet: public QObject
{
Q_OBJECT

public:

    // member functions

    NoobSet(int);

    // member variables

    QList<QGraphicsRectItem*> objects;
    int endPos;

public slots:

    void updateObjects();

signals:

    void killMe(int);
};

#endif // NOOBSET_H
