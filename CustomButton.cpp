#include "CustomButton.h"

CustomButton::CustomButton()
{

}

CustomButton::CustomButton(const QString textValue)
{
    this->setText(textValue);
}

CustomButton::CustomButton(const QString textValue, QWidget *paren)
{
    this->setText(textValue);
    this->setParent(paren);
}

CustomButton::CustomButton(QWidget *paren)
{
    this->setParent(paren);
}

void CustomButton::changeColor()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    QPalette p = pButton->palette();
    p.setColor(QPalette::Button, Qt::yellow);
    pButton->setPalette(p);
}
