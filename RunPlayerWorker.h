#ifndef RUNPLAYERWORKER_H
#define RUNPLAYERWORKER_H

#include <QObject>
#include "Player.h"
#include "PlayerState.h"
#include <QThread>

class RunPlayerWorker: public QObject
{
Q_OBJECT

public:

    /**
     * \brief Constructor
    */
    RunPlayerWorker();

public slots:

    /**
     * \brief Update Player State
     * Slot to handle updates of player state
    */
    void updatePlayerState(Player* player, bool isNotCollidingWithTop,
                           bool isNotCollidingWithBottom, bool isNotCollidingWithRight,
                           int xShift, int yShift);

    /**
     * \brief Flip Player
     * Slot to handle flipping of the player
    */
    void updateFlipPlayerState(Player* player);

signals:

    void doneUpdating(PlayerState state);
    void doneFlipping(PlayerState state);
};

#endif // RUNPLAYERWORKER_H
