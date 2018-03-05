#include "ScoreUpdater.h"
#include "Game.h"
#include <QFont>
#include <QDebug>

extern Game* game;

ScoreUpdater::ScoreUpdater(QGraphicsItem* parent):
    QGraphicsTextItem(parent), m_stepSize(5)
{
    m_score = 0;

    // set the properties of the text to be displayed
    setPlainText(QString::number(m_score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times", 16));
}

int ScoreUpdater::getScore()
{
    return m_score;
}

void ScoreUpdater::connectStepIncrementTimer()
{
    // create a new timer and connect its timeout to increment step size
    m_timerForStepSize = new QTimer;
    QObject::connect(m_timerForStepSize, SIGNAL(timeout()), this, SLOT(incrementStepSize()));
    m_timerForStepSize->start(2000);
}

void ScoreUpdater::disconnectStepIncrementTimer()
{
    // disconnect the timer to stop incrementing the step size after game termination
    // QObject::disconnect(m_timerForStepSize, SIGNAL(timeout()), this, SLOT(incrementStepSize()));
    m_timerForStepSize->disconnect();

    // Delete the timer
    delete m_timerForStepSize;

    /*
     * Set to NULL so that any attempt to dereference it
     * in the future will result in a runtime error indicating
     * that signal has not been disconnected yet.
    */

    m_timerForStepSize = NULL;
}

void ScoreUpdater::updateScore()
{
    // increase the score by stepsize
    m_score += m_stepSize;

    if(m_score > game->xShift *game->xShift *2000)
    {
        game->xShift++;
        qWarning() << m_score << ' ' << game->xShift;
    }

    // update the text
    setPlainText(QString::number(m_score));
}

void ScoreUpdater::incrementStepSize()
{
    // Disconnect the step increment timer if game has finished
    if(game->isFinished)
    {
        disconnectStepIncrementTimer();
        return;
    }

    // Try varying the value to be incermented
    m_stepSize = m_stepSize +1;

    // qWarning() << m_stepSize;
}
