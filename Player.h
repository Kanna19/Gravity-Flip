#ifndef PLAYER_H
#define PLAYER_H

class PlayerState;

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QPolygonF>
#include <QGraphicsItem>
#include "PlayerState.h"
#include <QMediaPlayer>

class Player: public QObject, public QGraphicsPixmapItem
{
Q_OBJECT

public:

    // member functions

    /**
     * \brief Constructor
    */
    Player();

    /**
     * \brief Constructor
     * \param Reference to Player
    */
    Player(const Player &player);

    /**
     * \brief Constructor
     * \param index
     * \param parent
    */
    Player(int index, QGraphicsItem* parent = 0);

    /**
     * \brief Flip Player
    */
    void flipPlayer();

    /**
     * \brief Is Not Colliding
     * \param area
    */
    bool isNotColliding(QGraphicsPolygonItem* area);

    /**
     * \brief Is Caught
     * \return true if caught, false otherwise
    */
    bool isCaught();

    /**
     * \brief Kill Player
    */
    void killPlayer();

    // member variables

    /**
     * \brief Player Index
    */
    int playerIndex;

    /**
     * \brief Run
    */
    QPixmap run[8];

    /**
     * \brief PixMapIndex
    */
    int pixmapIndex;

    /**
     * \brief Is Flipped
    */
    bool isFlipped;

    /**
     * \brief Is In Air
    */
    bool isInAir;

    /**
     * \brief Top Area
    */
    QGraphicsPolygonItem* topArea;

    /**
     * \brief Bottom Area
    */
    QGraphicsPolygonItem* bottomArea;

    /**
     * \brief Right Area
    */
    QGraphicsPolygonItem* rightArea;

    /**
     * \brief Step Sound Player
    */
    QMediaPlayer* stepSoundPlayer;

public slots:

    /**
     * \brief Run Player
    */
    void runPlayer();

    /**
     * \brief Slot Done Processing
     * Slot to be called after worker thread finishes processing the image
    */
    void doneProcessing(PlayerState state);

    /**
     * \brief Slot Done Flipping
     * Slot to be called after worker thread finishes flipping
    */
    void doneFlipping(PlayerState state);

signals:

    /**
     * \brief Request Update to player state
     * Requests an update to the player state
    */
    void requestUpdatePlayerState(Player* player, bool isNotCollidingWithTop,
                                  bool isNotCollidingWithBottom, bool isNotCollidingWithRight,
                                  int xShift, int yShift);
};

#endif // PLAYER_H
