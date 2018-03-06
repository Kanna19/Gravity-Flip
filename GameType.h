#ifndef GAMETYPE_H
#define GAMETYPE_H

/**
 * \brief Enum class to represent Game Type
 * If game is in SINGLEPLAYER or MULTIPLAYER then it is
 * expected to work correctly.
 *
 * If it is in NONE state then, some error occured during
 * runtime
*/

enum class GameType
{
    SINGLEPLAYER,
    MULTIPLAYER,
    NONE,
};

#endif // GAMETYPE_H
