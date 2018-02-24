#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include "Player.h"
#include <vector>

class Game : public QGraphicsView
{
public:

    // member functions
    Game(int cnt, QWidget* parent = 0);
    void keyPressEvent(QKeyEvent* event);
    void startSinglePlayerGame();
    void startMultiPlayerGame();

    // member variables
    QGraphicsScene* scene;

    bool isFinished;
    int player_cnt;
    std::vector <Player*> player;
};

#endif // GAME_H
