#ifndef INSTRUCTIONWINDOW_H
#define INSTRUCTIONWINDOW_H

#include <QMainWindow>
#include "CustomButton.h"
#include <QLabel>
#include "GameType.h"

class InstructionWindow: public QMainWindow
{
Q_OBJECT

public:

    // member functions

    /**
     * \brief Constructor
    */
    InstructionWindow(GameType type, QWidget* parent = 0);

    /**
     * \brief Display
     * Displays the instructions
    */
    void display();

private slots:

    // slots to handle key press events

    /**
     * \brief Slot to handle enter game
    */
    void handleEnterGame();

private:

    // private member variables

    /**
     * \brief Type of the game
    */
    GameType m_type;

    /**
     * \brief Label 1
    */
    QLabel* m_label1;

    /**
     * \brief Label 2
    */
    QLabel* m_label2;

    /**
     * \brief Enter Game
    */
    CustomButton* m_enterGame;
};

#endif // INSTRUCTIONWINDOW_H
