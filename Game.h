#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include "Player.h"
#include "BackgroundMusic.h"
#include "StepSound.h"
#include <vector>
#include "ScoreUpdater.h"
#include <QLabel>

class Game : public QGraphicsView
{
public:

    // member functions

    Game(int cnt, std::vector <int> playerIDMapping, QWidget* parent = 0);
    void keyPressEvent(QKeyEvent* event);
    void startSinglePlayerGame();
    void startMultiPlayerGame();

    // member variables

    QGraphicsScene* scene;
    BackgroundMusic* backgroundMusic;
    StepSound* stepSound[2];

    bool isFinished;
    int player_cnt;
    Player* player[2];

    std::vector <int> playerID;

    QPixmap images[2];
    QLabel* displayImage;
    ScoreUpdater* scoreUpdater;
};

#endif // GAME_H
