#ifndef SET1_H
#define SET1_H

#include <QGraphicsRectItem>
#include <QObject>

class Set1: public QObject
{
    Q_OBJECT
public:
    Set1();

    QList<QGraphicsRectItem*> objects;

public slots:
    void updateObjects();
};

#endif // SET1_H
