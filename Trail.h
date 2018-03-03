#ifndef TRAIL_H
#define TRAIL_H

#include <QGraphicsRectItem>
#include <QObject>

class Trail : public QObject, public QGraphicsRectItem
{
Q_OBJECT

public:

    // member functions

    Trail(qreal, qreal);

public slots:

    void updatePos();
};

#endif // TRAIL_H
