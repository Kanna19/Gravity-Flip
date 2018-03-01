#include "ScoreUpdater.h"
#include <QFont>
#include <QDebug>

ScoreUpdater::ScoreUpdater(QGraphicsItem* parent):
    QGraphicsTextItem(parent), m_stepSize(1)
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

void ScoreUpdater::updateScore()
{
    // increase the score by stepsize
    m_score += m_stepSize;

    // update the text
    setPlainText(QString::number(m_score));
}

void ScoreUpdater::incrementStepSize()
{
    // Try varying the value to be incermented
    m_stepSize = m_stepSize +1;
    // qWarning() << m_stepSize;
}
