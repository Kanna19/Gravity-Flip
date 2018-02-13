#include "Player.h"
#include <QList>
#include <QVector>
#include <QPointF>
#include <QGraphicsScene>
#include <Game.h>

extern Game* game;

Player::Player(QGraphicsItem* parent)
{
    setPixmap(QPixmap(":res/player/idle1.png").scaled(100,100,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    pixmapIndex = 0;

    isFlipped = false;

    // Describe a closed rectangle
    QPolygonF topRect;
    topRect.append(QPointF(0,0));
    topRect.append(QPointF(90,0));
    topRect.append(QPointF(90,5));
    topRect.append(QPointF(0,5));

    // Add the rectangle to the scene
    topArea = new QGraphicsPolygonItem(topRect, this);
    topArea->setPos(x(),y()-10);

    bottomArea = new QGraphicsPolygonItem(topRect, this);
    bottomArea->setPos(x(),y()+100);

    rightArea = new QGraphicsPolygonItem(topRect, this);
    rightArea->setRotation(90);
    rightArea->setPos(x()+100,y());

    for(int i = 1; i <= 8; i++)
    {
        run[i-1] = QPixmap(":/res/player/run" + QString::number(i) + ".png").scaled(100,100,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }



}

void Player::runPlayer()
{
    if( x() > 900) return ;
    pixmapIndex++;
    if(!isFlipped)
    {
        if(bottomArea->collidingItems().isEmpty())
        {
            setPos(x(),y()+3);
        }
        else
        {
            setPixmap(run[(pixmapIndex%48)/6]);
            if(rightArea->collidingItems().isEmpty()) setPos(x()+2,y());
            else setPos(x()-2,y());
        }
    }
    else
    {
        if(topArea->collidingItems().isEmpty())
        {
            setPos(x(),y()-3);
        }
        else
        {
            setPixmap(run[(pixmapIndex%48)/6].transformed(QTransform().rotate(180,Qt::XAxis)));
            if(rightArea->collidingItems().isEmpty()) setPos(x()+2,y());
            else setPos(x()-2,y());
        }

    }

     //setPos(x(),y());


}

void Player::flipPlayer()
{
    setPixmap(pixmap().transformed(QTransform().rotate(180,Qt::XAxis)));

    //change isFlipped
    isFlipped = (isFlipped+1)%2;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        flipPlayer();
    }
}
