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

    RunPlayerWorker();

public slots:

    void updatePlayerState(Player* player, bool isNotCollidingWithTop,
                           bool isNotCollidingWithBottom, bool isNotCollidingWithRight,
                           int xShift, int yShift);

    void updateFlipPlayerState(Player* player);

signals:

    void doneUpdating(PlayerState state);
    void doneFlipping(PlayerState state);
};

#endif // RUNPLAYERWORKER_H
