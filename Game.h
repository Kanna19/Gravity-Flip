#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include "Player.h"
class Game : public QGraphicsView
{
public:
    Game(QWidget* parent = 0);

    QGraphicsScene* scene;
    Player* player1;
    Player* player2;

    void keyPressEvent(QKeyEvent* event);

};

#endif // GAME_H
