#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QObject>

Game::Game(GameType type, std::vector <int> playerIDMapping, QWidget* parent):
    QGraphicsView(parent), gameType(type), gameState(GameState::PLAYING),
    playerID(playerIDMapping), xShift(2), yShift(3)
{
    // Create a new scene to display and set its properties
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1000, 500);
    setScene(scene);
    setFixedSize(1000, 500);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Set the alignment to top left corner
    setAlignment(Qt::AlignLeft|Qt::AlignTop);

    // Create a new scoreupdater
    scoreUpdater = new ScoreUpdater;

    // Show score if the game is singleplayer
    if(gameType == GameType::SINGLEPLAYER)
    {
        scene->addItem(scoreUpdater);
        scoreUpdater->setPos(50, 10);
    }

    else
    {
        displayImage = NULL;
    }

    // Store the idle images of both the players
    images[0] = QPixmap(":res/player/" + QString::number(playerID[0]) +"idle1.png");
    images[1] = QPixmap(":res/player/" + QString::number(playerID[1]) +"idle1.png");

    // Set the properties of the pause button
    pauseButton = new QPushButton(this);
    pauseButton->setIcon(QIcon(":/res/objects/pausebutton.png"));
    pauseButton->setIconSize(QSize(50, 50));
    pauseButton->setGeometry(QRect(QPoint(900, 0), QSize(50, 50)));
    connect(pauseButton, SIGNAL(released()), this, SLOT(handlePauseGame()));

    // Pause button is visible by default
    pauseButton->setVisible(true);

    // Set the properties of the resume button
    resumeButton = new QPushButton(this);
    resumeButton->setIcon(QIcon(":/res/objects/playbutton.png"));
    resumeButton->setIconSize(QSize(50, 50));
    resumeButton->setGeometry(QRect(QPoint(900, 0), QSize(50, 50)));
    connect(resumeButton, SIGNAL(released()), this, SLOT(handleResumeGame()));

    // Make the Resume button invisible by default
    resumeButton->setVisible(false);

    // Register the types which are to be sent/received via signal/slot mechanism
    qRegisterMetaType < Player > ("Player");
    qRegisterMetaType < PlayerState > ("PlayerState");

    // Start background music in a new thread
    backgroundMusic = new BackgroundMusic(1);
    backgroundMusic->moveToThread(backgroundMusic);
    backgroundMusic->start();

    // Create new object to update background regularly
    backgroundUpdater = new BackgroundUpdater;
}

void Game::keyPressEvent(QKeyEvent *event)
{
    // Donot respond to the key press event if game is already finished
    if(gameState == GameState::FINISHED)
    {
        // Accept this event (donot send it to its parent)
        event->accept();
        return;
    }

    // Check if pause key was pressed
    if(event->key() == Qt::Key_P)
    {
        // Pause the game if it isn't paused yet
        if(gameState != GameState::PAUSED)
        {
            pauseButton->click();
        }

        // Resume the game if it is paused
        else
        {
            resumeButton->click();
        }

        return;
    }

    // Donot flip the player if the game is paused
    if(gameState == GameState::PAUSED)
    {
        event->accept();
        return;
    }

    // The Game Type is Single Player
    if(gameType == GameType::SINGLEPLAYER)
    {
        if(event->key() == Qt::Key_Space)
        {
            // emit signal to worker thread to send a request to flip the player
            emit requestFlipPlayerUpdate(player[0]);
        }

        return;
    }

    // The Game Type is Multi Player

    // Flip the first player if 'M' was pressed
    if(event->key() == Qt::Key_M)
    {
        // emit signal to the worker thread to send a request to flip the player
        emit requestFlipPlayerUpdateForPlayer1(player[0]);
    }

    // Flip the second player if 'C' was pressed
    if(event->key() == Qt::Key_C)
    {
        // emit signal to the worker thread to send a request to flip the player
        emit requestFlipPlayerUpdateForPlayer2(player[1]);
    }
}

// This function is called when user clicks the X button while the game is running
void Game::closeEvent(QCloseEvent *event)
{
    // Close all running threads
    backgroundMusic->requestInterruption();

    /*
     * Set the setAccepted variable to true to
     * indicate that this function wants the event.
     * (Event doesn't propagate to parent widget)
     */

    event->accept();
}

/*
 * In Single Player Game:
 *
 *      player[0] represents the player
 *      player[1] represents the computer
*/

void Game::startSinglePlayerGame()
{
    // Create new sets
    set1 = new Set1(0);
    set2 = new Set2(set1->endPos);

    for(int i = 0; i < set1->objects.size(); i++)
    {
       scene->addItem(set1->objects[i]);
       set1->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
    }

    for(int i = 0; i < set2->objects.size(); i++)
    {
       scene->addItem(set2->objects[i]);
       set2->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
    }

    // Make game focusable
    setFocus();

    // Set the properties of the players

    // Create and add player 1 to the scene
    player[0] = new Player(0);
    scene->addItem(player[0]);
    player[0]->setPos(200, scene->height() -50 -120 +40);

    // Create and add computer to the scene
    player[1] = new Player(1);
    scene->addItem(player[1]);
    player[1]->setPos(50, scene->height() -50 -120 +40);

    /*
     * Create the required thread objects
     * These work like thread controllers.
    */

    threadForPlayer1 = new QThread;
    threadForPlayer2 = new QThread;

    /*
     * Create worker objects.
     * These objects will do work required on a different thread
    */

    workerForPlayer1 = new RunPlayerWorker;
    workerForPlayer2 = new RunPlayerWorker;

    // Move the workers to their respective threads
    workerForPlayer1->moveToThread(threadForPlayer1);
    workerForPlayer2->moveToThread(threadForPlayer2);

    // Connect all the signals required for the singleplayer game
    connectSignalsForSinglePlayerGame();

    // Trigger the start signals of the threads
    threadForPlayer1->start();
    threadForPlayer2->start();

    // Add image to show next to the score
    displayImage = new QLabel(this);
    displayImage->setPixmap(images[0].scaled(60, 60,
                                        Qt::KeepAspectRatio, Qt::SmoothTransformation));
    displayImage->setGeometry(QRect(QPoint(0, 0), QSize(60, 60)));
    displayImage->show();

    // Connect all the signals which are common to both single and multiplayer games
    connectCommonSignals();
}

/*
 * In Multi Player Game:
 *
 *      player[0] represents player 1
 *      player[1] represents player 2
*/

void Game::startMultiPlayerGame()
{
    // Create new sets
    set1 = new Set1(0);
    set2 = new Set2(set1->endPos);

    // Set the properties of the objects and add them to the scene
    for(int i = 0; i < set1->objects.size(); i++)
    {
       scene->addItem(set1->objects[i]);
       set1->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
    }

    for(int i = 0; i < set2->objects.size(); i++)
    {
       scene->addItem(set2->objects[i]);
       set2->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
    }

    // Make game focusable
    setFocus();

    // Add players

    // Create Player 1 and add to the scene
    player[0] = new Player(0);
    scene->addItem(player[0]);
    player[0]->setPos(200, scene->height() -50 -120 +40);

    // Create Player 2 and add to the scene
    player[1] = new Player(1);
    scene->addItem(player[1]);
    player[1]->setPos(50, scene->height() -50 -120 +40);

    /*
     * Create the required thread objects
     * These work like thread controllers.
    */

    threadForPlayer1 = new QThread;
    threadForPlayer2 = new QThread;

    /*
     * Create worker objects.
     * These objects will do work required on a different thread
    */

    workerForPlayer1 = new RunPlayerWorker;
    workerForPlayer2 = new RunPlayerWorker;

    // Move the workers to their respective threads
    workerForPlayer1->moveToThread(threadForPlayer1);
    workerForPlayer2->moveToThread(threadForPlayer2);

    // Connect all the signals required for the multiplayer game
    connectSignalsForMultiPlayerGame();

    // Trigger the start signals of the threads
    threadForPlayer1->start();
    threadForPlayer2->start();

    // Connect all the signals which are common to both single and multiplayer games
    connectCommonSignals();
}

void Game::connectSignalsForSinglePlayerGame()
{
    /*
     * Connect the requestUpdatePlayerState signal to the updatePlayerState of the worker
     * This connection helps in communicating from main thread to worker thread
     * This connection is used to signal that there is work ready for the worker thread
    */

    QObject::connect(player[0], SIGNAL(requestUpdatePlayerState(Player*,bool,bool,bool,int,int)),
            workerForPlayer1, SLOT(updatePlayerState(Player*,bool,bool,bool,int,int)));

    QObject::connect(player[1], SIGNAL(requestUpdatePlayerState(Player*,bool,bool,bool,int,int)),
            workerForPlayer2, SLOT(updatePlayerState(Player*,bool,bool,bool,int,int)));

    /*
     * Connect the doneUpdating signal of the worker to the doneProcessing of player(main thread)
     * This connection helps in communicating from worker thread to main thread
     * This connection is used to signal that worker thread has finished the required work
    */

    QObject::connect(workerForPlayer1, SIGNAL(doneUpdating(PlayerState)), player[0],
            SLOT(doneProcessing(PlayerState)));

    QObject::connect(workerForPlayer2, SIGNAL(doneUpdating(PlayerState)), player[1],
            SLOT(doneProcessing(PlayerState)));

    /*
     * Connect the requestFlipPlayerUpdate signal to the updateFlipPlayerState of the worker
     * This connection helps in communicating from main thread to worker thread
     * This connection is used to signal that there is work ready for the worker thread
    */

    QObject::connect(this, SIGNAL(requestFlipPlayerUpdate(Player*)),
                     workerForPlayer1, SLOT(updateFlipPlayerState(Player*)));

    /*
     * Connect the doneFlipping signal of the worker to the doneFlipping of player(main thread)
     * This connection helps in communicating from worker thread to main thread
     * This connection is used to signal that worker thread has finished the required work
     */

    QObject::connect(workerForPlayer1, SIGNAL(doneFlipping(PlayerState)),
                     player[0], SLOT(doneFlipping(PlayerState)));
}

void Game::connectSignalsForMultiPlayerGame()
{
    /*
     * Connect the requestUpdatePlayerState signal to the updatePlayerState of the worker
     * This connection helps in communicating from main thread to worker thread
     * This connection is used to signal that there is work ready for the worker thread
    */

    QObject::connect(player[0], SIGNAL(requestUpdatePlayerState(Player*,bool,bool,bool,int,int)),
            workerForPlayer1, SLOT(updatePlayerState(Player*,bool,bool,bool,int,int)));

    QObject::connect(player[1], SIGNAL(requestUpdatePlayerState(Player*,bool,bool,bool,int,int)),
            workerForPlayer2, SLOT(updatePlayerState(Player*,bool,bool,bool,int,int)));

    /*
     * Connect the doneUpdating signal of the worker to the doneProcessing of player(main thread)
     * This connection helps in communicating from worker thread to main thread
     * This connection is used to signal that worker thread has finished the required work
    */

    QObject::connect(workerForPlayer1, SIGNAL(doneUpdating(PlayerState)), player[0],
            SLOT(doneProcessing(PlayerState)));

    QObject::connect(workerForPlayer2, SIGNAL(doneUpdating(PlayerState)), player[1],
            SLOT(doneProcessing(PlayerState)));

    /*
     * Connect the requestFlipPlayerUpdate signal to the updateFlipPlayerState of the worker
     * This connection helps in communicating from main thread to worker thread
     * This connection is used to signal that there is work ready for the worker thread
    */

    QObject::connect(this, SIGNAL(requestFlipPlayerUpdateForPlayer1(Player*)),
                     workerForPlayer1, SLOT(updateFlipPlayerState(Player*)));

    QObject::connect(this, SIGNAL(requestFlipPlayerUpdateForPlayer2(Player*)),
                     workerForPlayer2, SLOT(updateFlipPlayerState(Player*)));

    /*
     * Connect the doneFlipping signal of the worker to the doneFlipping of player(main thread)
     * This connection helps in communicating from worker thread to main thread
     * This connection is used to signal that worker thread has finished the required work
     */

    QObject::connect(workerForPlayer1, SIGNAL(doneFlipping(PlayerState)),
                     player[0], SLOT(doneFlipping(PlayerState)));

    QObject::connect(workerForPlayer2, SIGNAL(doneFlipping(PlayerState)),
                     player[1], SLOT(doneFlipping(PlayerState)));
}

/*
 * In Multiplayer Game:
 *
 *      player[0] represents the 1st player
 *      player[1] represents the 2nd player
*/

void Game::connectCommonSignals()
{
    // Create a new timer object
    timer = new QTimer();

    // Connect the timeout signal of timer to the runPlayer slots of the players
    QObject::connect(timer, SIGNAL(timeout()), player[0], SLOT(runPlayer()));
    QObject::connect(timer, SIGNAL(timeout()), player[1], SLOT(runPlayer()));

    // Connect the timeout signal of timer to the updateObjects slots of the sets
    QObject::connect(timer, SIGNAL(timeout()), set1, SLOT(updateObjects()));
    QObject::connect(timer, SIGNAL(timeout()), set2, SLOT(updateObjects()));

    // Connect the timeout signal of timer to the background updater
    QObject::connect(timer, SIGNAL(timeout()), backgroundUpdater, SLOT(update()));

    // Connect the timeout signal of timer to the scoreupdater
    QObject::connect(timer, SIGNAL(timeout()), scoreUpdater, SLOT(updateScore()));

    // Set the time in milliseconds after which the timer has to signal timeout()
    timer->start(10);
}

void Game::reincarnateSet(int idx)
{
    // If set 1 was deleted then create new set1 and add to the screen
    if(idx == 1)
    {
        // Remove the existing items of set1 from the screen to prevent collisions
        for(int i = 0; i < set1->objects.size(); i++)
        {
            scene->removeItem(set1->objects[i]);
        }

        // Delete the set
        delete set1;

        // Create new set
        set1 = new Set1(set2->objects[0]->x() +set2->endPos);

        // Set properties of the set objects and add them to the scene
        for(int i = 0; i < set1->objects.size(); i++)
        {
            scene->addItem(set1->objects[i]);
            set1->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
        }

        // Connect the timeout signal of the timer to this newly created set
        // The previously existing connection would have been deleted
        QObject::connect(timer, SIGNAL(timeout()), set1, SLOT(updateObjects()));
    }

    // If set 2 was deleted then create new set 2 and add it to the scene
    else
    {
        // Remove the existing items of set2 from the screen to prevent collisions
        for(int i = 0; i < set2->objects.size(); i++)
        {
            scene->removeItem(set2->objects[i]);
        }

        // Delete the set
        delete set2;

        // Create new set
        set2 = new Set2(set1->objects[0]->x() +set1->endPos);

        // Set properties of the set objects and add them to the scene
        for(int i = 0; i < set2->objects.size(); i++)
        {
            scene->addItem(set2->objects[i]);
            set2->objects[i]->setBrush(QBrush(QImage(":/res/objects/tile2.png").scaled(40, 40)));
        }

        // Connect the timeout signal of the timer to this newly created set
        // The previously existing connection would have been deleted
        QObject::connect(timer, SIGNAL(timeout()), set2, SLOT(updateObjects()));
    }
}

void Game::handlePauseGame()
{
    // Hide the pause button
    pauseButton->setVisible(false);

    // Set the state of the game to paused
    gameState = GameState::PAUSED;

    /*
     * Reset the timer and set its timeout to a very large value.
     * This is effectively equivalent to disconnecting the timer.
     * disconnect() was not used because in order to connect the timer again,
     * all the signals have to be connected manually.
    */

    timer->start(10000000);

    // Display the resume button
    resumeButton->setVisible(true);
}

void Game::handleResumeGame()
{
    // Hide the resume button
    resumeButton->setVisible(false);

    // Set the state of the game to playing
    gameState = GameState::PLAYING;

    // reset the timer (reconnect the signals)
    timer->start(10);

    // show the pause button
    pauseButton->setVisible(true);
}
