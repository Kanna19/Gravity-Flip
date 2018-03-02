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
#include "Trail.h"

extern Game* game;
extern QWaitCondition soundWait;
extern QMutex mutex;

Player::Player(int index, QGraphicsItem* parent)
{
    playerIndex = index;
    int scaleFactor = 80;

    QPixmap image(":res/player/" + QString::number(game->playerID[playerIndex]) +
                         "idle1.png");

    setPixmap(image.scaled(scaleFactor,scaleFactor,
                          Qt::KeepAspectRatio, Qt::SmoothTransformation));

    pixmapIndex = 0;
    isFlipped = false;
    isInAir = false;

    // Describe a closed rectangle
    QPolygonF topRect;
    topRect.append(QPointF(0, 0));
    topRect.append(QPointF(65, 0));
    topRect.append(QPointF(65, 2));
    topRect.append(QPointF(0, 2));

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

        game->close();
        return;
    }

    pixmapIndex++;

    if(!isFlipped)
    {
        //if(bottomArea->collidingItems().isEmpty())
        if(isNotColliding(bottomArea))
        {
            if(!isNotColliding(rightArea)) setPos(x()-2, y() +3);
            else setPos(x(), y() +3);
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

            //if(rightArea->collidingItems().isEmpty())
            if(isNotColliding(rightArea))
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
        //if(topArea->collidingItems().isEmpty())
        if(isNotColliding(topArea))
        {
            if(!isNotColliding(rightArea)) setPos(x()-2, y() -3);
            else setPos(x(), y() -3);
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

            //if(rightArea->collidingItems().isEmpty())
            if(isNotColliding(rightArea))
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
    //if(topArea->collidingItems().isEmpty() && bottomArea->collidingItems().isEmpty())
    if(isNotColliding(topArea) && isNotColliding(bottomArea))
    {
        return;
    }

    setPixmap(pixmap().transformed(QTransform().rotate(180, Qt::XAxis)));

    // change isFlipped
    isFlipped = !isFlipped;
    if(game->player_cnt == 1 && this != game->player[1])
    {
        Trail* trail = new Trail(x()+75,y());
        QObject::connect(game->timer,SIGNAL(timeout()),trail,SLOT(updatePos()));
        game->scene->addItem(trail);
    }

}

bool Player::isNotColliding(QGraphicsPolygonItem* area)
{
    if(area->collidingItems().empty())
        return true;

    /*
     * There is no scoreboard in case of a multiplayer game
     * hence collision with it is not possible
    */

    if(game->player_cnt == 2)
        return false;

    // Ignore collisions with the score
    if(area->collidesWithItem(game->scoreUpdater))
        return true;

    QList<QGraphicsItem*> list = area->collidingItems();
    for(int i=0; i<list.size(); i++)
    {
        if(typeid(*list[i]) != typeid(Trail)) return false;
    }

    return true;
}
