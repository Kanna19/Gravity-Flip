#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QMainWindow>
#include "CustomButton.h"

class GameOverWindow: public QMainWindow
{
Q_OBJECT

public:

    // member functions

    /**
     * \brief Constructor
    */
    GameOverWindow(QWidget *parent = 0);

    /**
     * \brief Display the game over window
     * \param Index of the loser
    */
    void display(int loser);

    /**
     * \brief Reboot Code
     * Constant value to indicate that restart was selected
    */
    static int const EXIT_CODE_REBOOT;

private:

    // private member variables

    /**
     * \brief Exit Game
    */
    CustomButton* m_exitGame;

    /**
     * \brief Restart Game
    */
    CustomButton* m_restartGame;

private slots:

    // slots to handle key press events

    /**
     * \brief Function to handle exit game
    */
    void handleExitGame();

    /**
     * \brief Function to handle restart game
    */
    void handleRestartGame();
};

#endif // GAMEOVERWINDOW_H
