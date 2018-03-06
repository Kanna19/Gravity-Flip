#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class Player;

#include "Player.h"

class PlayerState
{

public:

    /**
     * \brief Constructor
    */
    PlayerState();

    /**
     * \brief Constructor
     * \param Reference to PlayerState
    */
    PlayerState(const PlayerState& state);

    /**
     * \brief Constructor
     * \param Pointer to Player
    */
    PlayerState(Player* player);

    /**
     * \brief X co-ordinate
    */
    qreal xPos;

    /**
     * \brief Y co-ordinate
    */
    qreal yPos;

    /**
     * \brief Pixmap Index
    */
    int pixmapIndex;

    /**
     * \brief Is the player in air
     * True if player is in air
     * False otherwise
    */
    bool isInAir;

    /**
     * \brief Is the player flipped
     * True if player is flipped
     * False otherwise
    */
    bool isFlipped;

    /**
     * \brief Is update to pixmap needed
     * True if update to pixmap is needed
     * False otherwise
    */
    bool isUpdateToPixMapNeeded;
};

#endif // PLAYERSTATE_H
