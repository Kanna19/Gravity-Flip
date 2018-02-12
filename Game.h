#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Player.h"
class Game : public QGraphicsView
{
public:
    Game();

    QGraphicsScene* scene;
    Player* player;

};

#endif // GAME_H
