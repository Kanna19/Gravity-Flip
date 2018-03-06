#ifndef NOOBSET_H
#define NOOBSET_H

#include <QGraphicsRectItem>
#include <QObject>

class NoobSet: public QObject
{
Q_OBJECT

public:

    // member functions
    /**
     * \brief Constructor
     * \param start_pos To set the starting position of set
     */
    NoobSet(int start_pos);

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

#endif // NOOBSET_H
