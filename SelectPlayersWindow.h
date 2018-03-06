#ifndef SELECTPLAYERSWINDOW_H
#define SELECTPLAYERSWINDOW_H

#include <QMainWindow>
#include "CustomButton.h"
#include <QLabel>
#include <QSignalMapper>
#include <vector>
#include "GameType.h"

class SelectPlayersWindow: public QMainWindow
{
Q_OBJECT

public:

    // member functions

    SelectPlayersWindow(GameType type, QWidget* parent = 0);
    void display();

private slots:

    void setPlayer1ID(int id);
    void setPlayer2ID(int id);

private:

    void updateDisplay();
    void createNewGame();

    // private member variables

    GameType m_type;
    QLabel* m_label;

    const int m_imageCount;
    std::vector <int> m_playerID;
    std::vector <CustomButton*> m_images;

    QSignalMapper* m_mapper;
};

#endif // SELECTPLAYERSWINDOW_H
