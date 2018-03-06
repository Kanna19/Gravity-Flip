#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>

class CustomButton: public QPushButton
{
Q_OBJECT

public:
    /**
     * \brief Default constructor
     */
    CustomButton();

    /**
     * \brief Constructor that takes only text as input
     */
    CustomButton(const QString textValue);

    /**
     * \brief Constructor that takes text and parent widget as input
     */
    CustomButton(const QString textValue, QWidget* paren);

    /**
     * \brief Constructor that takes only parent widget as input
     */
    CustomButton(QWidget* paren);

public slots:

    /**
     * \brief Changes the the color of button when pressed
     */
    void changeColor();
};

#endif // CUSTOMBUTTON_H
