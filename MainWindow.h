#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CustomButton.h"

class MainWindow: public QMainWindow
{
Q_OBJECT

public:

    // member functions

    /**
     * \brief Constructor
    */
    MainWindow(QWidget *parent = 0);

    /**
     * \brief Display
     * Displays the MainWindow
    */
    void display();

private slots:

    // slots to handle key press events

    /**
     * \brief Slot to handle singleplayer
    */
    void handleSinglePlayer();

    /**
     * \brief Slot to handle multiplayer
    */
    void handleMultiPlayer();

    /**
     * \brief Slot to handle exit game
    */
    void handleExitGame();

    /**
     * \brief Change the color
     * Change the color of the button on pressing
    */
    void changeColor();

private:

    // private member variables

    /**
     * \brief SinglePlayer Button
    */
    CustomButton* m_singlePlayer;

    /**
     * \brief MultiPlayer Button
    */
    QPushButton* m_multiPlayer;

    /**
     * \brief Exit Game Button
    */
    QPushButton* m_exitGame;
};

#endif // MAINWINDOW_H
