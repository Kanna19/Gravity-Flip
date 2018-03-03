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
#include <QCloseEvent>
#include <QTimer>
#include "Set2.h"

class Game : public QGraphicsView
{
Q_OBJECT

public:

    // member functions

    Game(int cnt, std::vector <int> playerIDMapping, QWidget* parent = 0);
    void keyPressEvent(QKeyEvent* event);
    void closeEvent(QCloseEvent* event);
    void startSinglePlayerGame();
    void startMultiPlayerGame();

    // member variables

    QTimer* timer;
    QGraphicsScene* scene;
    BackgroundMusic* backgroundMusic;
    StepSound* stepSound[2];
    Set2* set[2];

    bool isFinished;
    int player_cnt;
    Player* player[2];

    std::vector <int> playerID;

    QPixmap images[2];
    QLabel* displayImage;
    ScoreUpdater* scoreUpdater;

public slots:

    void reincarnateSet(int);
};

#endif // GAME_H
