#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include "Player.h"
#include "BackgroundMusic.h"
#include <vector>
#include "ScoreUpdater.h"
#include <QLabel>
#include <QCloseEvent>
#include <QTimer>
#include "Set1.h"
#include "Set2.h"
#include <QThread>
#include "RunPlayerWorker.h"
#include <QPushButton>
#include "BackgroundUpdater.h"

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
    BackgroundUpdater* backgroundUpdater;

    Set1* set1;
    Set2* set2[2];

    bool isPaused;
    bool isFinished;

    int player_cnt;
    Player* player[2];

    std::vector <int> playerID;

    QPixmap images[2];
    QLabel* displayImage;
    ScoreUpdater* scoreUpdater;

    QThread* threadForPlayer1;
    QThread* threadForPlayer2;

    RunPlayerWorker* workerForPlayer1;
    RunPlayerWorker* workerForPlayer2;

    QPushButton* pauseButton;
    QPushButton* resumeButton;

public slots:

    void reincarnateSet(int);

private slots:

    void handlePauseGame();
    void handleResumeGame();

signals:

    void requestFlipPlayerUpdate(Player* player);
    void requestFlipPlayerUpdateForPlayer1(Player* player);
    void requestFlipPlayerUpdateForPlayer2(Player* player);
};

#endif // GAME_H
