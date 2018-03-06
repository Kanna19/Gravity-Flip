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

    /**
     * \brief Constructor
     * \param type Type of the game
     * \param playerIDMapping Vector representing the choice of characters
     * \param parent Pointer to Parent of this Widget
    */
    Game(GameType type, std::vector <int> playerIDMapping, QWidget* parent = 0);

    /**
     * \brief Function called when Key press is detected
    */
    void keyPressEvent(QKeyEvent* event);

    /**
     * \brief Function called when X button is pressed
    */
    void closeEvent(QCloseEvent* event);

    /**
     * \brief Starts a SinglePlayer Game
    */
    void startSinglePlayerGame();

    /**
     * \brief Starts a MultiPlayer Game
    */
    void startMultiPlayerGame();

    /**
     * \brief Connects the signals which are common to both single and multiplayer games
    */
    void connectCommonSignals();

    /**
     * \brief Connects the signals required for singleplayer game
    */
    void connectSignalsForSinglePlayerGame();

    /**
     * \brief Connects the signals required for multiplayer game
    */
    void connectSignalsForMultiPlayerGame();

    // member variables

    /**
     * \brief timer
     * Used for updating the player position and score
    */
    QTimer* timer;

    /**
     * \brief scene
    */
    QGraphicsScene* scene;

    /**
     * \brief Background music
    */
    BackgroundMusic* backgroundMusic;

    /**
     * \brief Background updater
     * Object which is called by timer to update the background
    */
    BackgroundUpdater* backgroundUpdater;

    /**
     * \brief Set 1
    */
    Set1* set1;

    /**
     * \brief Set 2
    */
    Set2* set2;

    /**
     * \brief Type of the Game
     * Can either be GAMETYPE::SINGLEPLAYER or GAMETYPE::MULTIPLAYER
    */
    GameType gameType;

    /**
     * \brief State of the Game
     * Can either be GAMESTATE::PLAYING or GAMESTATE::PAUSED or GAMESTATE::FINISHED
    */
    GameState gameState;

    /**
     * \brief Information regarding the player
    */
    Player* player[2];

    /**
     * \brief Player to character Mapping
     * Vector representing the indices of characters chosen by the user
    */
    std::vector <int> playerID;

    /**
     * \brief Images
     * Image of the Player
    */
    QPixmap images[2];

    /**
     * \brief Display Image
     * Image to be displayed near the score
    */
    QLabel* displayImage;

    /**
     * \brief Score Updater
     * Object to store/update the score
    */
    ScoreUpdater* scoreUpdater;

    /**
     * \brief Thread For 1st Player
     * Operations on the first player are performed in this thread
    */
    QThread* threadForPlayer1;

    /**
     * \brief Thread for 2nd Player
     * Operations on the second player are performed in this thread
    */
    QThread* threadForPlayer2;

    /**
     * \brief Worker Object for 1st Thread
     * Worker Function to be executed on the 1st thread
    */
    RunPlayerWorker* workerForPlayer1;

    /**
     * \brief Worker Object for 2nd Thread
     * Worker Function to be executed on the 2nd thread
    */
    RunPlayerWorker* workerForPlayer2;

    /**
     * \brief Pause Button
    */
    QPushButton* pauseButton;

    /**
     * \brief Resume Button
    */
    QPushButton* resumeButton;

    /**
     * \brief Shift in x per 10 milli seconds
    */
    int xShift;

    /**
     * \brief Shift in y per 10 milli seconds
    */
    int yShift;

public slots:

    /**
     * \brief Regenerate the set
     * \param Index of the set
    */
    void reincarnateSet(int);

private slots:

    /**
     * \brief Slot to pause the game
    */
    void handlePauseGame();

    /**
     * \brief Slot to resume the game
    */
    void handleResumeGame();

signals:

    /**
     * \brief Send a request to flip the player
    */
    void requestFlipPlayerUpdate(Player* player);

    /**
     * \brief Send a request to flip player 1
    */
    void requestFlipPlayerUpdateForPlayer1(Player* player);

    /**
     * \brief Send a request to flip player 2
    */
    void requestFlipPlayerUpdateForPlayer2(Player* player);
};

#endif // GAME_H
