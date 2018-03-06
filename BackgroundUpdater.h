#ifndef BACKGROUNDUPDATER_H
#define BACKGROUNDUPDATER_H

#include <QObject>
#include <QBrush>

class BackgroundUpdater: public QObject
{
Q_OBJECT

public:

    // member functions
    /**
     * \brief Constructor
     */
    BackgroundUpdater();

    // member variables

    /**
     * \brief Used to store and update brush of game
     */
    QBrush brush;

    /**
     * \brief Is set to true if background has changed
     */
    bool isChanged;

public slots:

    /**
     * \brief Moves the background based on game->xShift
     */
    void update();
};

#endif // BACKGROUNDUPDATER_H
