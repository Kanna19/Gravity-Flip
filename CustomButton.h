#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>

class CustomButton: public QPushButton
{
Q_OBJECT

public:
    CustomButton();
    CustomButton(const QString textValue);
    CustomButton(const QString textValue, QWidget* paren);
    CustomButton(QWidget* paren);

public slots:
    void changeColor();
};

#endif // CUSTOMBUTTON_H
