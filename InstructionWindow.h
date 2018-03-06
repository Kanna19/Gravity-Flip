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

    InstructionWindow(GameType type, QWidget* parent = 0);
    void display();

private slots:

    // slots to handle key press events

    void handleEnterGame();

private:

    // private member variables

    GameType m_type;
    QLabel* m_label1;
    QLabel* m_label2;

    CustomButton* m_enterGame;
};

#endif // INSTRUCTIONWINDOW_H
