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
                           bool isNotCollidingWithBottom, bool isNotCollidingWithRight);

    void updateFlipPlayerState(Player* player/*, bool isNotCollidingWithTop,
                               bool isNotCollidingWithBottom*/);

signals:

    void doneUpdating(PlayerState state);
    void doneFlipping(PlayerState state);
};

#endif // RUNPLAYERWORKER_H
