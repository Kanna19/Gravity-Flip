#include "RunPlayerWorker.h"
#include <QDebug>

RunPlayerWorker::RunPlayerWorker()
{

}

void RunPlayerWorker::updatePlayerState
(Player *player, bool isNotCollidingWithTop,
 bool isNotCollidingWithBottom, bool isNotCollidingWithRight)

{
    /*
    if(thread()->isInterruptionRequested())
    {
        qWarning() << "dead";
        return;
    }
    */

    // qWarning() << player->x() << ' ' << player->y();
    PlayerState state(player);
    // qWarning() << state.xPos << ' ' << state.yPos;

    state.pixmapIndex++;

    if(!state.isFlipped)
    {
        if(isNotCollidingWithBottom)
        {
            if(!isNotCollidingWithRight)
            {
                state.xPos -= 2;
                state.yPos += 3;
            }

            else
            {
                state.yPos += 3;
            }

            state.isInAir = true;
        }

        else
        {
            if(state.isInAir)
            {
                player->stepSoundPlayer->play();
            }

            state.isInAir = false;
            state.isUpdateToPixMapNeeded = true;

            if(isNotCollidingWithRight)
            {
                ;
            }

            else
            {
                state.xPos -= 2;
            }
        }
    }

    else
    {
        if(isNotCollidingWithTop)
        {
            if(!isNotCollidingWithRight)
            {
                state.xPos -= 2;
                state.yPos -= 3;
            }

            else
            {
                state.yPos -= 3;
            }

            state.isInAir = true;
        }

        else
        {
            if(state.isInAir)
            {
                player->stepSoundPlayer->play();
            }

            state.isInAir = false;
            state.isUpdateToPixMapNeeded = true;

            if(isNotCollidingWithRight)
            {
                ;
            }

            else
            {
                state.xPos -= 2;
            }
        }
    }

    emit doneUpdating(state);
}

void RunPlayerWorker::updateFlipPlayerState(Player *player/*, bool isNotCollidingWithTop, bool isNotCollidingWithBottom*/)
{
    //qWarning() << thread()->currentThreadId();

    if(player->isInAir)
    {
        return;
    }

    PlayerState state(player);
    state.isFlipped = 1 -state.isFlipped;

    emit doneFlipping(state);
}
