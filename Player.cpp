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

extern Game* game;
extern QWaitCondition soundWait;
extern QMutex mutex;

Player::Player(int index, QGraphicsItem* parent)
{
    playerIndex = index;
    int scaleFactor = 80;
    setPixmap(QPixmap(":res/player/" + QString::number(game->playerID[playerIndex]) +
                      "idle1.png").scaled(scaleFactor,scaleFactor,
                        Qt::KeepAspectRatio, Qt::SmoothTransformation));

    pixmapIndex = 0;
    isFlipped = false;
    isInAir = false;

    // Describe a closed rectangle
    QPolygonF topRect;
    topRect.append(QPointF(0, 0));
    topRect.append(QPointF(70, 0));
    topRect.append(QPointF(70, 5));
    topRect.append(QPointF(0, 5));

    // Add the rectangles to the scene
    topArea = new QGraphicsPolygonItem(topRect, this);
    topArea->setPos(x(), y() -10);

    bottomArea = new QGraphicsPolygonItem(topRect, this);
    bottomArea->setPos(x(), y()+scaleFactor);

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
}

void Player::runPlayer()
{
    // Do nothing if game is already over
    if(game->isFinished)
    {
        return;
    }

    // Check these values
    if(x() > 900 || x() +100 < 0 || y() > 500 || y() +100 < 0)
    {
        game->isFinished = true;

        GameOverWindow* gameOverWindow = new GameOverWindow;
        gameOverWindow->display(playerIndex);

        game->backgroundMusic->requestInterruption();
        game->stepSound[0]->requestInterruption();
        game->stepSound[1]->requestInterruption();
        soundWait.wakeAll();

        game->close();
        return;
    }

    pixmapIndex++;

    if(!isFlipped)
    {
        if(bottomArea->collidingItems().isEmpty())
        {
            setPos(x(), y() +3);
            isInAir = true;
        }

        else
        {
            if(isInAir)
            {
                //mutex.lock();
                soundWait.wakeOne();
                //mutex.unlock();
            }

            isInAir = false;
            setPixmap(run[(pixmapIndex % 48) /6]);

            if(rightArea->collidingItems().isEmpty())
            {
                setPos(x(), y());
            }

            else
            {
                setPos(x() -2, y());
            }
        }
    }

    else
    {
        if(topArea->collidingItems().isEmpty())
        {
            setPos(x(), y() -3);
            isInAir = true;
        }

        else
        {
            if(isInAir)
            {
                //emit makeSound();
                //mutex.lock();
                //mutex.unlock();
                soundWait.wakeOne();
            }
            isInAir = false;

            setPixmap(run[(pixmapIndex % 48) /6].transformed(QTransform().rotate(180, Qt::XAxis)));

            if(rightArea->collidingItems().isEmpty())
            {
                setPos(x(), y());
            }

            else
            {
                setPos(x() -2, y());
            }
        }
    }
}

void Player::flipPlayer()
{
    // DONOT flip if player is in air
    if(topArea->collidingItems().isEmpty() && bottomArea->collidingItems().isEmpty())
    {
        return;
    }

    setPixmap(pixmap().transformed(QTransform().rotate(180, Qt::XAxis)));

    // change isFlipped
    isFlipped = (isFlipped +1) % 2;
}
