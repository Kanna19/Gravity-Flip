#include "Player.h"
#include <QList>
#include <QVector>
#include <QPointF>
#include <QGraphicsScene>
#include <Game.h>
#include <QDebug>
#include <QWaitCondition>
#include <QMutex>
#include "GameOverWindow.h"
#include <QLabel>
#include <typeinfo>
#include "Trail.h"
#include <QTest>

extern Game* game;

Player::Player()
{
}

Player::Player(const Player &player) : QObject(), QGraphicsPixmapItem()
{
    playerIndex = player.playerIndex;

    for(int i = 0; i < 8; i++)
    {
        run[i] = player.run[i];
    }

    pixmapIndex = player.pixmapIndex;
    isFlipped = player.isFlipped;
    isInAir = player.isInAir;

    topArea = player.topArea;
    bottomArea = player.bottomArea;
    rightArea = player.rightArea;
}

Player::Player(int index, QGraphicsItem* parent)
{
    // Set index of for players 1 and 2
    playerIndex = index;
    int scaleFactor = 80;

    // Set image of player
    QPixmap image(":res/player/" + QString::number(game->playerID[playerIndex]) +
                         "idle1.png");
    setPixmap(image.scaled(scaleFactor,scaleFactor,
                          Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Initialize variables
    pixmapIndex = 0;
    isFlipped = false;
    isInAir = false;

    // Describe a closed rectangle
    QPolygonF topRect;
    topRect.append(QPointF(0, 0));
    topRect.append(QPointF(65, 0));
    topRect.append(QPointF(65, 2));
    topRect.append(QPointF(0, 2));

    /* Create polygon items that surround the player
     * These rectangles are used to check for collisions
     * in various directions
     */
    // Add the rectangles to the scene
    topArea = new QGraphicsPolygonItem(topRect, this);
    topArea->setPos(x(), y() -10);

    bottomArea = new QGraphicsPolygonItem(topRect, this);
    bottomArea->setPos(x(), y() +scaleFactor);

    rightArea = new QGraphicsPolygonItem(topRect, this);
    rightArea->setRotation(90);
    rightArea->setPos(x() +scaleFactor, y());

    // Make the surrounding rectangles invisible
    topArea->setVisible(false);
    bottomArea->setVisible(false);
    rightArea->setVisible(false);

    // Set the corresponding running images
    for(int i = 1; i <= 8; i++)
    {
        run[i -1] = QPixmap(":/res/player/" + QString::number(game->playerID[playerIndex]) + "run" +
                            QString::number(i) + ".png").scaled(scaleFactor,scaleFactor,
                            Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }

    // Initialize step Sound
    stepSoundPlayer = new QMediaPlayer;
    stepSoundPlayer->setMedia(QUrl("qrc:/res/sounds/footsteps.mp3"));
}

void Player::runPlayer()
{
    // Do nothing if game is already over
    if(game->gameState == GameState::FINISHED)
    {
        return;
    }

    /* In single player mode if the computer reaches the
     * player the player dies and the game ends
     *
     * This portion checks if player is caught and ends the game accordingly
     */
    if(game->gameType== GameType::SINGLEPLAYER)
    {
        // Check if computer catches the player
        if(isCaught())
        {
            // Player was caught, game over.
            game->gameState = GameState::FINISHED;

            // Disconnect the timer from players, sets, backgroundupdater, score
            game->timer->disconnect();

            // Kill the player if computer catches him/her
            killPlayer();

            // Show the game window for 2 seconds before displaying gameoverwindow
            QTest::qWait(2000);

            // Create new game over window and display it
            GameOverWindow* gameOverWindow = new GameOverWindow;
            gameOverWindow->display(0);

            // Close game (GraphicsView)
            game->close();
            return;
        }
    }

    // Check if player crosses bounds
    if(x() > 900 || x() +80 < 0 || y() > 500 || y() +100 < 0)
    {
        game->gameState = GameState::FINISHED;

        GameOverWindow* gameOverWindow = new GameOverWindow;
        gameOverWindow->display(playerIndex);

        game->close();
        return;
    }

    // Emit signal to update player state
    emit requestUpdatePlayerState(this, isNotColliding(topArea),
                    isNotColliding(bottomArea), isNotColliding(rightArea),
                                  game->xShift, game->yShift);

     // Donot emit request until all previous requests were handled
    disconnect(game->timer, SIGNAL(timeout()), this, SLOT(runPlayer()));
}

void Player::doneProcessing(PlayerState state)
{
    /* Update all player state variables based on values
     * returned by runPlayerWorker
     */

    setPos(state.xPos, state.yPos);
    pixmapIndex = state.pixmapIndex;
    isInAir = state.isInAir;
    isFlipped = state.isFlipped;

    if(state.isUpdateToPixMapNeeded)
    {
        if(!state.isFlipped)
        {
            setPixmap(run[(pixmapIndex % 48) /6]);
        }

        else
        {
            setPixmap(run[(pixmapIndex % 48) /6].transformed(QTransform().
                                                             rotate(180, Qt::XAxis)));
        }
    }

    // Reconnect game timer to runPlayer after updating state
    connect(game->timer, SIGNAL(timeout()), this, SLOT(runPlayer()));
}

void Player::doneFlipping(PlayerState state)
{
    // Flip player if flipPlayer state was changed by runPlayerWorker
    setPixmap(pixmap().transformed(QTransform().rotate(180, Qt::XAxis)));
    isFlipped = state.isFlipped;

    /* In single player games player leaves a trail which the computer
     * picks up. This makes the computer flip it's
     * gravity at the right moments (or wrongs moments depending on player)
     * Since computer does waste time deciding to flip or press key (react
     * to the obstacle) it plays better than the player
     */

    if(game->gameType == GameType::SINGLEPLAYER && this != game->player[1])
    {
        Trail* trail = new Trail(x() +75, y());
        QObject::connect(game->timer, SIGNAL(timeout()), trail, SLOT(updatePos()));
        game->scene->addItem(trail);
    }
}

void Player::flipPlayer()
{
    // DONOT flip if player is in air
    if(isNotColliding(topArea) && isNotColliding(bottomArea))
    {
        return;
    }

    setPixmap(pixmap().transformed(QTransform().rotate(180, Qt::XAxis)));

    // Change isFlipped if not in air
    isFlipped = !isFlipped;
}

bool Player::isNotColliding(QGraphicsPolygonItem* area)
{
    if(area->collidingItems().empty())
    {
        return true;
    }

    /*
     * There is no scoreboard in case of a multiplayer game
     * hence collision with it is not possible
    */

    if(game->gameType== GameType::MULTIPLAYER)
    {
        return false;
    }

    // Ignore collisions with the score
    if(area->collidesWithItem(game->scoreUpdater))
    {
        return true;
    }

    return true;
}

bool Player::isCaught()
{
    // Check for collision between player and bot
    if(game->player[1]->rightArea->collidesWithItem(game->player[0]))
    {
        return true;
    }

    return false;
}

void Player::killPlayer()
{
    // Set the player's image to dead
    QPixmap deadImage(":res/player/" + QString::number(game->playerID[0]) +
                      "dead1.png");
    game->player[0]->setPixmap(deadImage.scaled(70, 70, Qt::KeepAspectRatio,
                                                Qt::SmoothTransformation));

    // Flip the image depending on the direction of gravity
    if(game->player[0]->isFlipped)
    {
        game->player[0]->setPixmap(game->player[0]->pixmap().
                transformed(QTransform().rotate(180, Qt::XAxis)));
    }

    // Set the computer's image to idle
    QPixmap idleImage(game->images[1]);
    game->player[1]->setPixmap(idleImage.scaled(80, 80, Qt::KeepAspectRatio,
                                                Qt::SmoothTransformation));

    // Flip the image depending on the direction of gravity
    if(game->player[1]->isFlipped)
    {
        game->player[1]->setPixmap(game->player[1]->pixmap().
                transformed(QTransform().rotate(180, Qt::XAxis)));
    }
}
