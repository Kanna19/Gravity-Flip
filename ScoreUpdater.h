#ifndef SCOREUPDATER_H
#define SCOREUPDATER_H

#include <QTimer>
#include <QGraphicsTextItem>

class ScoreUpdater: public QGraphicsTextItem
{
Q_OBJECT

public:

    // member functions

    /**
     * \brief Constructor
    */
    ScoreUpdater(QGraphicsItem* parent = 0);

    /**
     * \brief Get Score
     * \return score
    */
    int getScore();

private slots:

    /**
     * \brief Update Score
     * Increase the score by m_stepSize
    */
    void updateScore();

private:

    // private member variables

    /**
     * \brief Score
     * Score of the player
    */
    int m_score;

    /**
     * \brief Step Size
    */
    int m_stepSize;
};

#endif // SCOREUPDATER_H
