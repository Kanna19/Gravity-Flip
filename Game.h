#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QThread>
#include <QLabel>
#include <QCloseEvent>
#include <QTimer>
#include <QPushButton>
#include <vector>
#include "Player.h"
#include "BackgroundMusic.h"
#include "ScoreUpdater.h"
#include "NoobSet.h"
#include "Set1.h"
#include "Set2.h"
#include "RunPlayerWorker.h"
#include "BackgroundUpdater.h"
#include "GameType.h"
#include "GameState.h"

class Game : public QGraphicsView
{
Q_OBJECT

public:

    // member functions

    Game(GameType type, std::vector <int> playerIDMapping, QWidget* parent = 0);
    void keyPressEvent(QKeyEvent* event);
    void closeEvent(QCloseEvent* event);
    void startSinglePlayerGame();
    void startMultiPlayerGame();
    void connectCommonSignals();
    void connectSignalsForSinglePlayerGame();
    void connectSignalsForMultiPlayerGame();

    // member variables

    QTimer* timer;
    QGraphicsScene* scene;
    BackgroundMusic* backgroundMusic;
    BackgroundUpdater* backgroundUpdater;

    NoobSet* noobSet;
    Set1* set1;
    Set2* set2;

    GameType gameType;
    GameState gameState;

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

    int xShift;
    int yShift;

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
