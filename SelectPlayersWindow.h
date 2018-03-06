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

    /**
     * \brief Constructor
     * \param Type
    */
    SelectPlayersWindow(GameType type, QWidget* parent = 0);

    /**
     * \brief Display
     * Displays the SelectPlayersWindow
    */
    void display();

private slots:

    /**
     * \brief Set id of player 1
    */
    void setPlayer1ID(int id);

    /**
     * \brief Set id of player 2
    */
    void setPlayer2ID(int id);

private:

    /**
     * \brief Update the display
    */
    void updateDisplay();

    /**
     * \brief Create new game
    */
    void createNewGame();

    // private member variables

    /**
     * \brief Game Type
    */
    GameType m_type;

    /**
     * \brief Label
    */
    QLabel* m_label;

    /**
     * \brief Image Count
     * Number of player images available
    */
    const int m_imageCount;

    /**
     * \brief Player to character Mapping
     * Vector representing the indices of characters chosen by the user
    */
    std::vector <int> m_playerID;

    /**
     * \brief Images to be displayed on the buttons
    */
    std::vector <CustomButton*> m_images;

    /**
     * \brief Mapper
    */
    QSignalMapper* m_mapper;
};

#endif // SELECTPLAYERSWINDOW_H
