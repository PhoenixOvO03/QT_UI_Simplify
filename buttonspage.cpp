#include "buttonspage.h"

#include <QLabel>

ButtonsPage::ButtonsPage(QWidget *parent)
    : QWidget{parent}
{
    new QLabel("buttons page", this);
}
