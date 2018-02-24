#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include "Player.h"

class Game : public QGraphicsView
{
public:

    // member functions
    Game(QWidget* parent = 0);
    void keyPressEvent(QKeyEvent* event);

    // member variables
    QGraphicsScene* scene;
    Player* player1;
    Player* player2;
};

#endif // GAME_H
