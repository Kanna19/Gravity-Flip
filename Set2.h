#ifndef SET2_H
#define SET2_H

#include <QGraphicsRectItem>
#include <QObject>

class Set2: public QObject
{
Q_OBJECT

public:

    // member functions
    /**
     * \brief Constructor
     * \param startPos To set the starting position of set
     */
    Set2(int startPos);

    // member variables
    /**
     * \brief List of all objects in the set
     */
    QList<QGraphicsRectItem*> objects;

    /**
     * \brief Total length of the set
     */
    int endPos;

public slots:

    /**
     * \brief Move objects based on game->xShift
     */
    void updateObjects();

signals:

    /**
     * \brief Sends signal to game to destroy this set
     * \param idx Type of set to be destroyed
     */
    void killMe(int idx);
};

#endif // SET2_H
