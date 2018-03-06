#ifndef TRAIL_H
#define TRAIL_H

#include <QGraphicsRectItem>
#include <QObject>

class Trail : public QObject, public QGraphicsRectItem
{
Q_OBJECT

public:

    // member functions
    /**
     * \brief Constructor
     * \param xPos Used to set position on x-Axis
     * \param yPos Used to set position on y-Axis
     */
    Trail(qreal, qreal);

public slots:

    /**
     * \brief Moves the trail based on game->xShift
     */
    void updatePos();
};

#endif // TRAIL_H
