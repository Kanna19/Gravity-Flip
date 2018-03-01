#ifndef INSTRUCTIONWINDOW_H
#define INSTRUCTIONWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>


class InstructionWindow: public QMainWindow
{
Q_OBJECT

public:

    // member functions

    InstructionWindow(int cnt, QWidget* parent = 0);
    void display();

private slots:

    // slots to handle key press events

    void handleEnterGame();

private:

    // private member variables
    QPushButton* m_enterGame;

    int m_cnt;
    QLabel* m_label1;
    QLabel* m_label2;
};

#endif // INSTRUCTIONWINDOW_H
