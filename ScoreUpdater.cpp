#include "ScoreUpdater.h"
#include "Game.h"
#include <QFont>

extern Game* game;

ScoreUpdater::ScoreUpdater(QGraphicsItem* parent):
    QGraphicsTextItem(parent), m_stepSize(5)
{
    // Set initial  score to 0
    m_score = 0;

    // Set the properties of the text to be displayed
    setPlainText(QString::number(m_score));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times", 16));
}

int ScoreUpdater::getScore()
{
    return m_score;
}

void ScoreUpdater::updateScore()
{
    // Increase the score by stepsize
    m_score += m_stepSize;

    // Update vertical and horizontal speed when certain score is reached
    if(m_score > game->xShift *game->xShift *2000)
    {
        game->xShift++;
        game->yShift++;
    }

    // Update the text
    setPlainText(QString::number(m_score));
}
